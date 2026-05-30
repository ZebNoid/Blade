#include "WindowSurfaceRuntime.h"

#include <memory>
#include <windowsx.h>

#include "App/AppBackend.h"
#include "Components/Native/Label/NativeLabel.h"
#include "Components/Window/NativeWindow.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

auto PointFromLParam(LPARAM lParam) -> Api::Point
{
    return {
        .x = GET_X_LPARAM(lParam),
        .y = GET_Y_LPARAM(lParam)
    };
}

auto ToClientPoint(HWND hwnd, POINT point) -> Api::Point
{
    ScreenToClient(hwnd, &point);
    return {point.x, point.y};
}

auto ScreenPoint(HWND hwnd, LPARAM lParam) -> POINT
{
    POINT point{
        .x = GET_X_LPARAM(lParam),
        .y = GET_Y_LPARAM(lParam)
    };

    ClientToScreen(hwnd, &point);
    return point;
}

auto PaintLabels(AppBackend& backend, HDC hdc) -> void
{
    backend.nodes().forEach(
        [&backend, hdc](NativeNode& node)
        {
            auto* label = dynamic_cast<NativeLabel*>(node.native.get());
            if (label) label->paint(hdc, backend.resources(), backend.renderNodes());
        }
    );
}

auto PaintBuffered(HWND hwnd, HDC target, AppBackend& backend) -> void
{
    const auto rect = HwndApi::GetClientRect(hwnd);
    if (rect.width <= 0 || rect.height <= 0) return;

    auto memoryDc = CreateCompatibleDC(target);
    auto bitmap = CreateCompatibleBitmap(target, rect.width, rect.height);
    auto oldBitmap = SelectObject(memoryDc, bitmap);

    RenderApi::Fill(memoryDc, rect, backend.resources().windowBrush());
    PaintLabels(backend, memoryDc);
    BitBlt(target, 0, 0, rect.width, rect.height, memoryDc, 0, 0, SRCCOPY);

    SelectObject(memoryDc, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(memoryDc);
}

auto HitLabel(AppBackend& backend, Api::Point point, bool requireDrop = false) -> NativeLabel*
{
    NativeLabel* result = nullptr;
    int resultOrder = -1;

    backend.nodes().forEach(
        [&](NativeNode& node)
        {
            auto* label = dynamic_cast<NativeLabel*>(node.native.get());
            if (!label || !label->hitTest(point)) return;
            if (requireDrop && !label->wantsDrop()) return;

            const auto* render = backend.renderNodes().get(node.id);
            const auto order = render ? render->order : 0;
            if (!result || order >= resultOrder)
            {
                result = label;
                resultOrder = order;
            }
        }
    );

    return result;
}

auto LabelById(AppBackend& backend, Api::Id id) -> NativeLabel*
{
    const auto* node = backend.nodes().get(id);
    return node ? dynamic_cast<NativeLabel*>(node->native.get()) : nullptr;
}

auto ShowContextMenu(AppBackend& backend, HWND hwnd, Api::Point point, POINT screenPoint, Api::MenuTrigger trigger) -> bool
{
    auto* label = HitLabel(backend, point);
    if (!label || !label->hasContextMenu(trigger)) return false;

    const auto shown = label->showContextMenu(trigger, screenPoint);
    if (shown) HwndApi::Invalidate(hwnd);
    return shown;
}

} // namespace

auto WindowSurfaceRuntime::Attach(AppBackend& backend, NativeWindow& window) -> void
{
    window.router().on(
        WM_ERASEBKGND,
        [](HWND, UINT, WPARAM, LPARAM) -> int
        {
            return 1;
        }
    );

    window.router().on(
        WM_PAINT,
        [&backend](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            PAINTSTRUCT paint{};
            const auto hdc = BeginPaint(hwnd, &paint);
            PaintBuffered(hwnd, hdc, backend);
            EndPaint(hwnd, &paint);
            return 0;
        }
    );

    auto pressedLabel = std::make_shared<Api::Id>(Api::InvalidId);
    auto focusedLabel = std::make_shared<Api::Id>(Api::InvalidId);

    window.setDropTargetResolver(
        [&backend, &window](POINT screenPoint) -> Api::Id
        {
            auto* label = HitLabel(backend, ToClientPoint(window.handle(), screenPoint), true);
            return label ? label->id() : Api::InvalidId;
        }
    );

    window.router().on(
        WM_LBUTTONDOWN,
        [&backend, pressedLabel, focusedLabel](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            auto* label = HitLabel(backend, PointFromLParam(lParam));
            if (!label) return 1;

            if (*focusedLabel != label->id())
            {
                if (auto* previous = LabelById(backend, *focusedLabel); previous && previous->focus(backend.renderNodes(), false)) HwndApi::Invalidate(hwnd);
                *focusedLabel = label->id();
                if (label->focus(backend.renderNodes(), true)) HwndApi::Invalidate(hwnd);
            }

            *pressedLabel = label->id();
            SetCapture(hwnd);
            if (label->mouseDown(backend.renderNodes())) HwndApi::Invalidate(hwnd);
            return 0;
        }
    );

    window.router().on(
        WM_LBUTTONUP,
        [&backend, pressedLabel](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto menuShown = ShowContextMenu(backend, hwnd, PointFromLParam(lParam), ScreenPoint(hwnd, lParam), Api::MenuTrigger::LeftClick);

            if (*pressedLabel != Api::InvalidId)
            {
                if (GetCapture() == hwnd) ReleaseCapture();
                if (auto* label = LabelById(backend, *pressedLabel); label && label->mouseUp(backend.renderNodes())) HwndApi::Invalidate(hwnd);
                *pressedLabel = Api::InvalidId;
                return 0;
            }

            return menuShown ? 0 : 1;
        }
    );

    window.router().on(
        WM_MBUTTONUP,
        [&backend](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            return ShowContextMenu(backend, hwnd, PointFromLParam(lParam), ScreenPoint(hwnd, lParam), Api::MenuTrigger::MiddleClick) ? 0 : 1;
        }
    );

    window.router().on(
        WM_CONTEXTMENU,
        [&backend, &window](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            POINT screenPoint{
                .x = GET_X_LPARAM(lParam),
                .y = GET_Y_LPARAM(lParam)
            };

            const auto clientPoint = ToClientPoint(window.handle(), screenPoint);
            return ShowContextMenu(backend, hwnd, clientPoint, screenPoint, Api::MenuTrigger::RightClick) ? 0 : 1;
        }
    );
}

} // namespace Blade::Backend

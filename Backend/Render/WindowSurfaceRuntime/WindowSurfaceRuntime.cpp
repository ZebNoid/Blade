#include "WindowSurfaceRuntime.h"

#include <memory>
#include <vector>
#include <windowsx.h>

#include "App/AppBackend.h"
#include "Components/Native/Label/NativeLabel.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Components/Window/NativeWindow.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

struct VirtualHit
{
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;
    NativeLabel* label = nullptr;

    auto valid() const -> bool { return surface || label; }
};

struct PaintItem
{
    int order = 0;
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;
    NativeLabel* label = nullptr;
};

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

auto PaintVirtuals(AppBackend& backend, HDC hdc) -> void
{
    std::vector<PaintItem> items;

    backend.nodes().forEach(
        [&backend, &items](NativeNode& node)
        {
            const auto order = node.order;

            if (auto* surface = dynamic_cast<RenderSurface*>(node.native.get())) items.push_back({order, node.id, surface, nullptr});
            else if (auto* label = dynamic_cast<NativeLabel*>(node.native.get())) items.push_back({order, node.id, nullptr, label});
        }
    );

    std::ranges::sort(
        items,
        [](const auto& left, const auto& right)
        {
            if (left.order != right.order) return left.order < right.order;
            return left.id < right.id;
        }
    );

    for (const auto& item : items)
    {
        if (item.surface) item.surface->paint(hdc, backend.resources(), backend.renderNodes());
        if (item.label) item.label->paint(hdc, backend.resources(), backend.renderNodes());
    }
}

auto PaintBuffered(HWND hwnd, HDC target, AppBackend& backend) -> void
{
    const auto rect = HwndApi::GetClientRect(hwnd);
    if (rect.width <= 0 || rect.height <= 0) return;

    auto memoryDc = CreateCompatibleDC(target);
    auto bitmap = CreateCompatibleBitmap(target, rect.width, rect.height);
    auto oldBitmap = SelectObject(memoryDc, bitmap);

    RenderApi::Fill(memoryDc, rect, backend.resources().windowBrush());
    PaintVirtuals(backend, memoryDc);
    BitBlt(target, 0, 0, rect.width, rect.height, memoryDc, 0, 0, SRCCOPY);

    SelectObject(memoryDc, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(memoryDc);
}

auto HitVirtual(AppBackend& backend, Api::Point point, bool requireDrop = false) -> VirtualHit
{
    VirtualHit result;
    int resultOrder = -1;

    backend.nodes().forEach(
        [&](NativeNode& node)
        {
            auto* surface = dynamic_cast<RenderSurface*>(node.native.get());
            auto* label = dynamic_cast<NativeLabel*>(node.native.get());
            const auto hit = surface ? surface->hitTest(point) : label && label->hitTest(point);
            if (!hit) return;

            const auto wantsDrop = surface ? surface->wantsDrop() : label->wantsDrop();
            if (requireDrop && !wantsDrop) return;

            const auto order = node.order;
            if (!result.valid() || order > resultOrder || (order == resultOrder && node.id > result.id))
            {
                result = {node.id, surface, label};
                resultOrder = order;
            }
        }
    );

    return result;
}

auto HitId(const VirtualHit& hit) -> Api::Id
{
    return hit.valid() ? hit.id : Api::InvalidId;
}

auto VirtualById(AppBackend& backend, Api::Id id) -> VirtualHit
{
    const auto* node = backend.nodes().get(id);
    if (!node) return {};

    auto* surface = dynamic_cast<RenderSurface*>(node->native.get());
    auto* label = dynamic_cast<NativeLabel*>(node->native.get());
    return {id, surface, label};
}

auto Hover(AppBackend& backend, VirtualHit hit, bool hovered) -> bool
{
    if (hit.surface) return hit.surface->hover(backend.renderNodes(), hovered);
    return hit.label && hit.label->hover(backend.renderNodes(), hovered);
}

auto DragOver(AppBackend& backend, VirtualHit hit, bool active) -> bool
{
    if (hit.surface) return hit.surface->dragOver(backend.renderNodes(), active);
    return hit.label && hit.label->dragOver(backend.renderNodes(), active);
}

auto MouseDown(AppBackend& backend, VirtualHit hit) -> bool
{
    if (hit.surface) return hit.surface->mouseDown(backend.renderNodes());
    return hit.label && hit.label->mouseDown(backend.renderNodes());
}

auto MouseUp(AppBackend& backend, VirtualHit hit) -> bool
{
    if (hit.surface) return hit.surface->mouseUp(backend.renderNodes());
    return hit.label && hit.label->mouseUp(backend.renderNodes());
}

auto Focus(AppBackend& backend, VirtualHit hit, bool focused) -> bool
{
    if (hit.surface) return hit.surface->focus(backend.renderNodes(), focused);
    return hit.label && hit.label->focus(backend.renderNodes(), focused);
}

auto ShowContextMenu(AppBackend& backend, HWND hwnd, Api::Point point, POINT screenPoint, Api::MenuTrigger trigger) -> bool
{
    const auto hit = HitVirtual(backend, point);
    if (!hit.valid()) return false;

    const auto hasMenu = hit.surface ? hit.surface->hasContextMenu(trigger) : hit.label->hasContextMenu(trigger);
    if (!hasMenu) return false;

    const auto shown = hit.surface
        ? hit.surface->showContextMenu(trigger, screenPoint)
        : hit.label->showContextMenu(trigger, screenPoint);

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
    auto hoveredLabel = std::make_shared<Api::Id>(Api::InvalidId);
    auto dragOverLabel = std::make_shared<Api::Id>(Api::InvalidId);

    window.setDropTargetResolver(
        [&backend, &window, dragOverLabel](POINT screenPoint) -> Api::Id
        {
            const auto hit = HitVirtual(backend, ToClientPoint(window.handle(), screenPoint), true);
            const auto target = HitId(hit);
            if (*dragOverLabel == target) return target;

            if (DragOver(backend, VirtualById(backend, *dragOverLabel), false)) HwndApi::Invalidate(window.handle());
            *dragOverLabel = target;
            if (DragOver(backend, hit, true)) HwndApi::Invalidate(window.handle());
            return target;
        }
    );

    window.setDropDragLeaveHandler(
        [&backend, &window, dragOverLabel]
        {
            if (DragOver(backend, VirtualById(backend, *dragOverLabel), false)) HwndApi::Invalidate(window.handle());
            *dragOverLabel = Api::InvalidId;
        }
    );

    window.router().on(
        WM_MOUSEMOVE,
        [&backend, hoveredLabel](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto hit = HitVirtual(backend, PointFromLParam(lParam));
            const auto hoveredId = HitId(hit);
            if (*hoveredLabel == hoveredId) return 1;

            if (Hover(backend, VirtualById(backend, *hoveredLabel), false)) HwndApi::Invalidate(hwnd);
            *hoveredLabel = hoveredId;
            if (Hover(backend, hit, true)) HwndApi::Invalidate(hwnd);

            TRACKMOUSEEVENT event{
                .cbSize = sizeof(TRACKMOUSEEVENT),
                .dwFlags = TME_LEAVE,
                .hwndTrack = hwnd
            };
            TrackMouseEvent(&event);
            return hit.valid() ? 0 : 1;
        }
    );

    window.router().on(
        WM_MOUSELEAVE,
        [&backend, hoveredLabel](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            if (Hover(backend, VirtualById(backend, *hoveredLabel), false)) HwndApi::Invalidate(hwnd);
            *hoveredLabel = Api::InvalidId;
            return 0;
        }
    );

    window.router().on(
        WM_LBUTTONDOWN,
        [&backend, pressedLabel, focusedLabel](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto hit = HitVirtual(backend, PointFromLParam(lParam));
            if (!hit.valid()) return 1;

            if (*focusedLabel != HitId(hit))
            {
                if (Focus(backend, VirtualById(backend, *focusedLabel), false)) HwndApi::Invalidate(hwnd);
                *focusedLabel = HitId(hit);
                if (Focus(backend, hit, true)) HwndApi::Invalidate(hwnd);
            }

            *pressedLabel = HitId(hit);
            SetCapture(hwnd);
            if (MouseDown(backend, hit)) HwndApi::Invalidate(hwnd);
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
                if (MouseUp(backend, VirtualById(backend, *pressedLabel))) HwndApi::Invalidate(hwnd);
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

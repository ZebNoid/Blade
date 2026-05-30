#include "WindowSurfaceRuntime.h"

#include <memory>
#include <vector>
#include <windowsx.h>

#include "App/AppBackend.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Components/Window/NativeWindow.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

struct PaintItem
{
    int order = 0;
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;
};

struct SurfaceHit
{
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;

    auto valid() const -> bool { return surface != nullptr; }
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

            if (auto* surface = dynamic_cast<RenderSurface*>(node.native.get())) items.push_back({order, node.id, surface});
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
        item.surface->paint(hdc, backend.resources(), backend.renderNodes());
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

auto HitSurface(AppBackend& backend, Api::Point point, bool requireDrop = false) -> SurfaceHit
{
    SurfaceHit result;
    int resultOrder = -1;

    backend.nodes().forEach(
        [&](NativeNode& node)
        {
            auto* surface = dynamic_cast<RenderSurface*>(node.native.get());
            if (!surface || !surface->hitTest(point)) return;

            if (requireDrop && !surface->wantsDrop()) return;

            const auto order = node.order;
            if (!result.valid() || order > resultOrder || (order == resultOrder && node.id > result.id))
            {
                result = {node.id, surface};
                resultOrder = order;
            }
        }
    );

    return result;
}

auto HitId(const SurfaceHit& hit) -> Api::Id
{
    return hit.valid() ? hit.id : Api::InvalidId;
}

auto SurfaceById(AppBackend& backend, Api::Id id) -> SurfaceHit
{
    const auto* node = backend.nodes().get(id);
    if (!node) return {};

    auto* surface = dynamic_cast<RenderSurface*>(node->native.get());
    return {id, surface};
}

template <typename Apply>
auto ApplySurfaceState(AppBackend& backend, HWND hwnd, SurfaceHit hit, Apply apply) -> void
{
    if (hit.valid() && apply(*hit.surface, backend.renderNodes())) HwndApi::Invalidate(hwnd);
}

auto ShowContextMenu(AppBackend& backend, HWND hwnd, Api::Point point, POINT screenPoint, Api::MenuTrigger trigger) -> bool
{
    const auto hit = HitSurface(backend, point);
    if (!hit.valid()) return false;

    if (!hit.surface->hasContextMenu(trigger)) return false;

    const auto shown = hit.surface->showContextMenu(trigger, screenPoint);
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

    auto pressedId = std::make_shared<Api::Id>(Api::InvalidId);
    auto focusedId = std::make_shared<Api::Id>(Api::InvalidId);
    auto hoveredId = std::make_shared<Api::Id>(Api::InvalidId);
    auto dragOverId = std::make_shared<Api::Id>(Api::InvalidId);

    window.setDropTargetResolver(
        [&backend, &window, dragOverId](POINT screenPoint) -> Api::Id
        {
            const auto hit = HitSurface(backend, ToClientPoint(window.handle(), screenPoint), true);
            const auto target = HitId(hit);
            if (*dragOverId == target) return target;

            ApplySurfaceState(backend, window.handle(), SurfaceById(backend, *dragOverId), [](auto& surface, auto& renderNodes) { return surface.dragOver(renderNodes, false); });
            *dragOverId = target;
            ApplySurfaceState(backend, window.handle(), hit, [](auto& surface, auto& renderNodes) { return surface.dragOver(renderNodes, true); });
            return target;
        }
    );

    window.setDropDragLeaveHandler(
        [&backend, &window, dragOverId]
        {
            ApplySurfaceState(backend, window.handle(), SurfaceById(backend, *dragOverId), [](auto& surface, auto& renderNodes) { return surface.dragOver(renderNodes, false); });
            *dragOverId = Api::InvalidId;
        }
    );

    window.router().on(
        WM_MOUSEMOVE,
        [&backend, hoveredId](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto hit = HitSurface(backend, PointFromLParam(lParam));
            const auto targetId = HitId(hit);
            if (*hoveredId == targetId) return 1;

            ApplySurfaceState(backend, hwnd, SurfaceById(backend, *hoveredId), [](auto& surface, auto& renderNodes) { return surface.hover(renderNodes, false); });
            *hoveredId = targetId;
            ApplySurfaceState(backend, hwnd, hit, [](auto& surface, auto& renderNodes) { return surface.hover(renderNodes, true); });

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
        [&backend, hoveredId](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            ApplySurfaceState(backend, hwnd, SurfaceById(backend, *hoveredId), [](auto& surface, auto& renderNodes) { return surface.hover(renderNodes, false); });
            *hoveredId = Api::InvalidId;
            return 0;
        }
    );

    window.router().on(
        WM_LBUTTONDOWN,
        [&backend, pressedId, focusedId](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto hit = HitSurface(backend, PointFromLParam(lParam));
            if (!hit.valid()) return 1;

            if (*focusedId != HitId(hit))
            {
                ApplySurfaceState(backend, hwnd, SurfaceById(backend, *focusedId), [](auto& surface, auto& renderNodes) { return surface.focus(renderNodes, false); });
                *focusedId = HitId(hit);
                ApplySurfaceState(backend, hwnd, hit, [](auto& surface, auto& renderNodes) { return surface.focus(renderNodes, true); });
            }

            *pressedId = HitId(hit);
            SetCapture(hwnd);
            ApplySurfaceState(backend, hwnd, hit, [](auto& surface, auto& renderNodes) { return surface.mouseDown(renderNodes); });
            return 0;
        }
    );

    window.router().on(
        WM_LBUTTONUP,
        [&backend, pressedId](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto menuShown = ShowContextMenu(backend, hwnd, PointFromLParam(lParam), ScreenPoint(hwnd, lParam), Api::MenuTrigger::LeftClick);

            if (*pressedId != Api::InvalidId)
            {
                if (GetCapture() == hwnd) ReleaseCapture();
                ApplySurfaceState(backend, hwnd, SurfaceById(backend, *pressedId), [](auto& surface, auto& renderNodes) { return surface.mouseUp(renderNodes); });
                *pressedId = Api::InvalidId;
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

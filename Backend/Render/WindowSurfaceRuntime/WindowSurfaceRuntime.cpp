#include "WindowSurfaceRuntime.h"

#include <memory>

#include "App/AppBackend.h"
#include "Components/Window/NativeWindow.h"
#include "Render/SurfaceHitTest/SurfaceHitTest.h"
#include "Render/SurfaceInteraction/SurfaceInteraction.h"
#include "Render/SurfacePainter/SurfacePainter.h"
#include "WinApi/HwndApi/HwndApi.h"

namespace Blade::Backend {

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
            Surface::Painter::PaintBuffered(hwnd, hdc, backend);
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
            const auto hit = Surface::HitTest::Hit(backend, HwndApi::ToClientPoint(window.handle(), screenPoint), true);
            const auto target = Surface::HitTest::Id(hit);
            if (*dragOverId == target) return target;

            Surface::Interaction::SetDragOver(backend, window.handle(), Surface::HitTest::ById(backend, *dragOverId), false);
            *dragOverId = target;
            Surface::Interaction::SetDragOver(backend, window.handle(), hit, true);
            return target;
        }
    );

    window.setDropDragLeaveHandler(
        [&backend, &window, dragOverId]
        {
            Surface::Interaction::SetDragOver(backend, window.handle(), Surface::HitTest::ById(backend, *dragOverId), false);
            *dragOverId = Api::InvalidId;
        }
    );

    window.router().on(
        WM_MOUSEMOVE,
        [&backend, hoveredId](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto hit = Surface::HitTest::Hit(backend, HwndApi::PointFromLParam(lParam));
            const auto targetId = Surface::HitTest::Id(hit);
            if (*hoveredId == targetId) return 1;

            Surface::Interaction::SetHover(backend, hwnd, Surface::HitTest::ById(backend, *hoveredId), false);
            *hoveredId = targetId;
            Surface::Interaction::SetHover(backend, hwnd, hit, true);

            HwndApi::TrackMouseLeave(hwnd);
            return hit.valid() ? 0 : 1;
        }
    );

    window.router().on(
        WM_MOUSELEAVE,
        [&backend, hoveredId](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            Surface::Interaction::SetHover(backend, hwnd, Surface::HitTest::ById(backend, *hoveredId), false);
            *hoveredId = Api::InvalidId;
            return 0;
        }
    );

    window.router().on(
        WM_LBUTTONDOWN,
        [&backend, pressedId, focusedId](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto hit = Surface::HitTest::Hit(backend, HwndApi::PointFromLParam(lParam));
            if (!hit.valid()) return 1;

            if (*focusedId != Surface::HitTest::Id(hit))
            {
                Surface::Interaction::SetFocus(backend, hwnd, Surface::HitTest::ById(backend, *focusedId), false);
                *focusedId = Surface::HitTest::Id(hit);
                Surface::Interaction::SetFocus(backend, hwnd, hit, true);
            }

            *pressedId = Surface::HitTest::Id(hit);
            HwndApi::CaptureMouse(hwnd);
            Surface::Interaction::MouseDown(backend, hwnd, hit);
            return 0;
        }
    );

    window.router().on(
        WM_LBUTTONUP,
        [&backend, pressedId](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto point = HwndApi::PointFromLParam(lParam);
            const auto menuShown = Surface::Interaction::ShowContextMenu(backend, hwnd, point, HwndApi::ToScreenPoint(hwnd, point), Api::MenuTrigger::LeftClick);

            if (*pressedId != Api::InvalidId)
            {
                if (HwndApi::HasMouseCapture(hwnd)) HwndApi::ReleaseMouseCapture(hwnd);
                Surface::Interaction::MouseUp(backend, hwnd, Surface::HitTest::ById(backend, *pressedId));
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
            const auto point = HwndApi::PointFromLParam(lParam);
            return Surface::Interaction::ShowContextMenu(backend, hwnd, point, HwndApi::ToScreenPoint(hwnd, point), Api::MenuTrigger::MiddleClick) ? 0 : 1;
        }
    );

    window.router().on(
        WM_CONTEXTMENU,
        [&backend, &window](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            const auto point = HwndApi::PointFromLParam(lParam);
            POINT screenPoint{point.x, point.y};

            const auto clientPoint = HwndApi::ToClientPoint(window.handle(), screenPoint);
            return Surface::Interaction::ShowContextMenu(backend, hwnd, clientPoint, screenPoint, Api::MenuTrigger::RightClick) ? 0 : 1;
        }
    );
}

} // namespace Blade::Backend

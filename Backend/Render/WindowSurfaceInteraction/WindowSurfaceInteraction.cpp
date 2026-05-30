#include "WindowSurfaceInteraction.h"

#include "App/AppBackend.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "WinApi/HwndApi/HwndApi.h"

namespace Blade::Backend {

namespace Surface::Interaction {

namespace {

template <typename Apply>
auto ApplySurfaceState(AppBackend& backend, HWND hwnd, SurfaceHit hit, Apply apply) -> void
{
    if (hit.valid() && apply(*hit.surface, backend.renderNodes())) HwndApi::Invalidate(hwnd);
}

} // namespace

auto SetDragOver(AppBackend& backend, HWND hwnd, SurfaceHit hit, bool active) -> void
{
    ApplySurfaceState(backend, hwnd, hit, [active](auto& surface, auto& renderNodes) { return surface.dragOver(renderNodes, active); });
}

auto SetHover(AppBackend& backend, HWND hwnd, SurfaceHit hit, bool hovered) -> void
{
    ApplySurfaceState(backend, hwnd, hit, [hovered](auto& surface, auto& renderNodes) { return surface.hover(renderNodes, hovered); });
}

auto SetFocus(AppBackend& backend, HWND hwnd, SurfaceHit hit, bool focused) -> void
{
    ApplySurfaceState(backend, hwnd, hit, [focused](auto& surface, auto& renderNodes) { return surface.focus(renderNodes, focused); });
}

auto MouseDown(AppBackend& backend, HWND hwnd, SurfaceHit hit) -> void
{
    ApplySurfaceState(backend, hwnd, hit, [](auto& surface, auto& renderNodes) { return surface.mouseDown(renderNodes); });
}

auto MouseUp(AppBackend& backend, HWND hwnd, SurfaceHit hit) -> void
{
    ApplySurfaceState(backend, hwnd, hit, [](auto& surface, auto& renderNodes) { return surface.mouseUp(renderNodes); });
}

auto ShowContextMenu(AppBackend& backend, HWND hwnd, Api::Point point, POINT screenPoint, Api::MenuTrigger trigger) -> bool
{
    const auto hit = Surface::HitTest::Hit(backend, point);
    if (!hit.valid()) return false;

    if (!hit.surface->hasContextMenu(trigger)) return false;

    const auto shown = hit.surface->showContextMenu(trigger, screenPoint);
    if (shown) HwndApi::Invalidate(hwnd);
    return shown;
}

} // namespace Surface::Interaction

} // namespace Blade::Backend

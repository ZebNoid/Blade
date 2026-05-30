#include "VirtualElement.h"

#include "Components/RenderSurface/RenderSurface.h"

namespace Blade::Backend {

auto VirtualElement::valid() const -> bool
{
    return surface != nullptr;
}

auto VirtualElement::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) const -> void
{
    if (surface) surface->paint(hdc, resources, renderNodes);
}

auto VirtualElement::hitTest(Api::Point point) const -> bool
{
    return surface && surface->hitTest(point);
}

auto VirtualElement::wantsDrop() const -> bool
{
    return surface && surface->wantsDrop();
}

auto VirtualElement::hasContextMenu(Api::MenuTrigger trigger) const -> bool
{
    return surface && surface->hasContextMenu(trigger);
}

auto VirtualElement::showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) const -> bool
{
    return surface && surface->showContextMenu(trigger, screenPoint);
}

auto VirtualElement::hover(RenderRegistry& renderNodes, bool hovered) const -> bool
{
    return surface && surface->hover(renderNodes, hovered);
}

auto VirtualElement::dragOver(RenderRegistry& renderNodes, bool active) const -> bool
{
    return surface && surface->dragOver(renderNodes, active);
}

auto VirtualElement::mouseDown(RenderRegistry& renderNodes) const -> bool
{
    return surface && surface->mouseDown(renderNodes);
}

auto VirtualElement::mouseUp(RenderRegistry& renderNodes) const -> bool
{
    return surface && surface->mouseUp(renderNodes);
}

auto VirtualElement::focus(RenderRegistry& renderNodes, bool focused) const -> bool
{
    return surface && surface->focus(renderNodes, focused);
}

} // namespace Blade::Backend

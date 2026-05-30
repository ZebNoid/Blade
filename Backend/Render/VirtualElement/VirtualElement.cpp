#include "VirtualElement.h"

#include "Components/Native/Label/NativeLabel.h"
#include "Components/RenderSurface/RenderSurface.h"

namespace Blade::Backend {

auto VirtualElement::valid() const -> bool
{
    return surface || label;
}

auto VirtualElement::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) const -> void
{
    if (surface) surface->paint(hdc, resources, renderNodes);
    if (label) label->paint(hdc, resources, renderNodes);
}

auto VirtualElement::hitTest(Api::Point point) const -> bool
{
    if (surface) return surface->hitTest(point);
    return label && label->hitTest(point);
}

auto VirtualElement::wantsDrop() const -> bool
{
    if (surface) return surface->wantsDrop();
    return label && label->wantsDrop();
}

auto VirtualElement::hasContextMenu(Api::MenuTrigger trigger) const -> bool
{
    if (surface) return surface->hasContextMenu(trigger);
    return label && label->hasContextMenu(trigger);
}

auto VirtualElement::showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) const -> bool
{
    if (surface) return surface->showContextMenu(trigger, screenPoint);
    return label && label->showContextMenu(trigger, screenPoint);
}

auto VirtualElement::hover(RenderRegistry& renderNodes, bool hovered) const -> bool
{
    if (surface) return surface->hover(renderNodes, hovered);
    return label && label->hover(renderNodes, hovered);
}

auto VirtualElement::dragOver(RenderRegistry& renderNodes, bool active) const -> bool
{
    if (surface) return surface->dragOver(renderNodes, active);
    return label && label->dragOver(renderNodes, active);
}

auto VirtualElement::mouseDown(RenderRegistry& renderNodes) const -> bool
{
    if (surface) return surface->mouseDown(renderNodes);
    return label && label->mouseDown(renderNodes);
}

auto VirtualElement::mouseUp(RenderRegistry& renderNodes) const -> bool
{
    if (surface) return surface->mouseUp(renderNodes);
    return label && label->mouseUp(renderNodes);
}

auto VirtualElement::focus(RenderRegistry& renderNodes, bool focused) const -> bool
{
    if (surface) return surface->focus(renderNodes, focused);
    return label && label->focus(renderNodes, focused);
}

} // namespace Blade::Backend

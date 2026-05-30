#include "MaterializerRules.h"

namespace Blade {

auto MaterializerRules::IsContextArea(const WidgetTree& widget) -> bool
{
    return widget.type == Api::WidgetTypes::ContextArea;
}

auto MaterializerRules::HasEvent(const WidgetTree& widget, Api::Events event) -> bool
{
    return widget.events.find(event) != widget.events.end();
}

auto MaterializerRules::ShouldMaterialize(const WidgetTree& widget, const LayoutNode& layout) -> bool
{
    return layout.layoutType == LayoutType::None || IsNativeContextArea(widget);
}

auto MaterializerRules::ShouldMaterialize(const WidgetTree& widget) -> bool
{
    return widget.layoutType == LayoutType::None || IsNativeContextArea(widget);
}

auto MaterializerRules::SameRect(const LayoutNode* previousLayout, const LayoutNode& layout) -> bool
{
    if (!previousLayout) return false;

    const auto& a = previousLayout->rect;
    const auto& b = layout.rect;
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}

auto MaterializerRules::HasNativeDescendant(const WidgetTree& widget) -> bool
{
    if (widget.layoutType == LayoutType::None) return true;

    for (const auto& child : widget.children)
    {
        if (HasNativeDescendant(child)) return true;
    }

    return false;
}

auto MaterializerRules::IsNativeContextArea(const WidgetTree& widget) -> bool
{
    return IsContextArea(widget) && !widget.children.empty() && !HasNativeDescendant(widget.children.front());
}

} // namespace Blade

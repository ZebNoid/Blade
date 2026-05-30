#include "LayoutLeafChildren.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade::Layout::LeafChildren {

namespace {

auto ChildRect(const LayoutNode& child, const Api::Rect& contentRect) -> Api::Rect
{
    return {
        contentRect.x,
        contentRect.y,
        child.layoutType == LayoutType::None ? child.desiredSize.width : contentRect.width,
        child.layoutType == LayoutType::None ? child.desiredSize.height : contentRect.height
    };
}

} // namespace

auto Measure(LayoutNode& node) -> Api::Size
{
    int maxWidth = 0;
    int maxHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = node.desiredSize };
        const auto size = Layout::Engine::Measure(childCtx);

        maxWidth = max(maxWidth, size.width);
        maxHeight = max(maxHeight, size.height);
    }

    return { maxWidth, maxHeight };
}

auto Arrange(LayoutNode& node, const Api::Rect& contentRect) -> void
{
    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = ChildRect(child, contentRect) };
        Layout::Engine::Arrange(childCtx);
    }
}

} // namespace Blade::Layout::LeafChildren

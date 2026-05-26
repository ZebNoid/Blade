#include "LayoutLeafChildren.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutLeafChildren::Measure(LayoutNode& node) -> Api::Size
{
    int maxWidth = 0;
    int maxHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = node.desiredSize };
        const auto size = LayoutEngine::Measure(childCtx);
        const auto marginSize = LayoutGeometry::Inflate(size, child.layout.box.margin);

        maxWidth = max(maxWidth, marginSize.width);
        maxHeight = max(maxHeight, marginSize.height);
    }

    return { maxWidth, maxHeight };
}

auto LayoutLeafChildren::Arrange(LayoutNode& node, const Api::Rect& contentRect) -> void
{
    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = ChildRect(child, contentRect) };
        LayoutEngine::Arrange(childCtx);
    }
}

auto LayoutLeafChildren::ChildRect(const LayoutNode& child, const Api::Rect& contentRect) -> Api::Rect
{
    const auto childContentRect = LayoutGeometry::Deflate(contentRect, child.layout.box.margin);

    return {
        childContentRect.x,
        childContentRect.y,
        child.layoutType == LayoutType::None ? child.desiredSize.width : childContentRect.width,
        child.layoutType == LayoutType::None ? child.desiredSize.height : childContentRect.height
    };
}

} // namespace Blade

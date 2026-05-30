#include "LayoutLeaf.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLeafChildren/LayoutLeafChildren.h"
#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"


namespace Blade::Layout::Leaf {

auto Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;

    node.desiredSize = node.layout.size;

    const auto childrenSize = Layout::LeafChildren::Measure(node);

    if (node.desiredSize.width == 0)
    {
        node.desiredSize.width = childrenSize.width;
    }

    if (node.desiredSize.height == 0)
    {
        node.desiredSize.height = childrenSize.height;
    }

    node.desiredSize = Layout::Geometry::Constrain(Layout::Geometry::Inflate(node.desiredSize, node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;
    const auto contentRect = Layout::Geometry::Deflate(ctx.rect, node.layout.box.padding);

    Layout::LeafChildren::Arrange(node, contentRect);
}

} // namespace Blade::Layout::Leaf

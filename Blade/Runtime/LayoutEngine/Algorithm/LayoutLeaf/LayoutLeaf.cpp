#include "LayoutLeaf.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLeafChildren/LayoutLeafChildren.h"
#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"


namespace Blade {

auto LayoutLeaf::Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;

    node.desiredSize = node.layout.size;

    const auto childrenSize = LayoutLeafChildren::Measure(node);

    if (node.desiredSize.width == 0)
    {
        node.desiredSize.width = childrenSize.width;
    }

    if (node.desiredSize.height == 0)
    {
        node.desiredSize.height = childrenSize.height;
    }

    node.desiredSize = LayoutGeometry::Inflate(node.desiredSize, node.layout.box.padding);
    return node.desiredSize;
}

auto LayoutLeaf::Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;
    const auto contentRect = LayoutGeometry::Deflate(ctx.rect, node.layout.box.padding);

    LayoutLeafChildren::Arrange(node, contentRect);
}

} // namespace Blade

#include "LayoutVirtual.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"

namespace Blade {

auto LayoutVirtual::Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;
    node.desiredSize = {};
    const auto available = Layout::Geometry::Deflate({0, 0, ctx.available.width, ctx.available.height}, node.layout.box.padding).size();

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = available };
        node.desiredSize = LayoutEngine::Measure(childCtx);
    }

    if (node.layout.size.width > 0) node.desiredSize.width = node.layout.size.width;
    if (node.layout.size.height > 0) node.desiredSize.height = node.layout.size.height;

    node.desiredSize = Layout::Geometry::Constrain(Layout::Geometry::Inflate(node.desiredSize, node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto LayoutVirtual::Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;
    const auto contentRect = Layout::Geometry::Deflate(ctx.rect, node.layout.box.padding);

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = contentRect };
        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

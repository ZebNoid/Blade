#include "LayoutStack.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade::Layout::Stack {

namespace {

auto MeasureChildren(LayoutNode& node, Api::Size available) -> Api::Size
{
    int maxWidth = 0;
    int maxHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = available };
        const auto size = LayoutEngine::Measure(childCtx);

        maxWidth = max(maxWidth, size.width);
        maxHeight = max(maxHeight, size.height);
    }

    return { maxWidth, maxHeight };
}

} // namespace

auto Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;
    const auto children = MeasureChildren(node, ctx.available);

    node.desiredSize = Layout::Geometry::Constrain(Layout::Geometry::Inflate(children, node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;
    const auto contentRect = Layout::Geometry::Deflate(ctx.rect, node.layout.box.padding);

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = contentRect };
        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade::Layout::Stack

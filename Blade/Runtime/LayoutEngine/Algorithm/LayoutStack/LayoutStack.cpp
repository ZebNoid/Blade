#include "LayoutStack.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutStack::Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;

    int maxWidth = 0;
    int maxHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = ctx.available };
        const auto size = LayoutEngine::Measure(childCtx);
        const auto marginSize = LayoutGeometry::Inflate(size, child.layout.box.margin);

        maxWidth = max(maxWidth, marginSize.width);
        maxHeight = max(maxHeight, marginSize.height);
    }

    node.desiredSize = LayoutGeometry::Inflate({ maxWidth, maxHeight }, node.layout.box.padding);
    return node.desiredSize;
}

auto LayoutStack::Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;
    const auto contentRect = LayoutGeometry::Deflate(ctx.rect, node.layout.box.padding);

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = LayoutGeometry::Deflate(contentRect, child.layout.box.margin) };
        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

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

        maxWidth = max(maxWidth, size.width);
        maxHeight = max(maxHeight, size.height);
    }

    node.desiredSize = LayoutGeometry::Constrain(LayoutGeometry::Inflate({ maxWidth, maxHeight }, node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto LayoutStack::Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;
    const auto contentRect = LayoutGeometry::Deflate(ctx.rect, node.layout.box.padding);

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = contentRect };
        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

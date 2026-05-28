#include "LayoutVirtual.h"

#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"

namespace Blade {

auto LayoutVirtual::Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;
    node.desiredSize = {};

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = ctx.available };
        node.desiredSize = LayoutEngine::Measure(childCtx);
    }

    return node.desiredSize;
}

auto LayoutVirtual::Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .rect = ctx.rect };
        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

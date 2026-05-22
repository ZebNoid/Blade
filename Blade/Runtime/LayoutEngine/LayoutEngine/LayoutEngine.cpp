#include "LayoutEngine.h"


namespace Blade {


auto LayoutEngine::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    // leaf/native widgets
    if (node.children.empty())
    {
        return node.desiredSize;
    }

    int maxWidth = 0;
    int totalHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{
            .node = &child,
            .available = ctx.available
        };

        const auto size = Measure(childCtx);

        maxWidth = max(maxWidth, size.width);

        totalHeight += size.height;
    }

    node.desiredSize = {
        maxWidth,
        totalHeight
    };

    return node.desiredSize;
}

auto LayoutEngine::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    node.rect = ctx.rect;

    int cursorY = ctx.rect.y;

    for (auto& child : node.children)
    {
        const auto size = child.desiredSize;

        Api::Rect childRect{
            ctx.rect.x,
            cursorY,
            size.width,
            size.height
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        Arrange(childCtx);

        cursorY += size.height;
    }
}


} // namespace

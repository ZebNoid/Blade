#include "LayoutStack.h"

#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutStack::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    int maxWidth = 0;
    int maxHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{
            .node = &child,
            .available = ctx.available
        };

        const auto size =
            LayoutEngine::Measure(
                childCtx
            );

        maxWidth = max(
            maxWidth,
            size.width
        );

        maxHeight = max(
            maxHeight,
            size.height
        );
    }

    const auto& padding =
        node.layout.layout.padding;

    node.desiredSize = {
        maxWidth +
        padding.left +
        padding.right,

        maxHeight +
        padding.top +
        padding.bottom
    };

    return node.desiredSize;
}

auto LayoutStack::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto& padding =
        node.layout.layout.padding;

    Api::Rect contentRect{
        ctx.rect.x + padding.left,
        ctx.rect.y + padding.top,
        ctx.rect.width -
        padding.left -
        padding.right,
        ctx.rect.height -
        padding.top -
        padding.bottom
    };

    for (auto& child : node.children)
    {
        LayoutContext childCtx{
            .node = &child,
            .rect = contentRect
        };

        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

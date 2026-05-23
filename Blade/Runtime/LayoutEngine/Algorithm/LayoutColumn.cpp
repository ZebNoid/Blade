#include "LayoutColumn.h"

#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutColumn::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    int maxWidth = 0;
    int totalHeight = 0;

    bool first = true;

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

        if (!first)
        {
            totalHeight +=
                node.layout.gap;
        }

        first = false;

        maxWidth = max(
            maxWidth,
            size.width
        );

        totalHeight +=
            size.height;
    }

    const auto& padding =
        node.layout.box.padding;

    node.desiredSize = {
        maxWidth +
        padding.left +
        padding.right,

        totalHeight +
        padding.top +
        padding.bottom
    };

    return node.desiredSize;
}

auto LayoutColumn::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto& padding =
        node.layout.box.padding;

    int cursorY =
        ctx.rect.y + padding.top;

    const int x =
        ctx.rect.x + padding.left;

    const int width =
        ctx.rect.width -
        padding.left -
        padding.right;

    bool first = true;

    for (auto& child : node.children)
    {
        if (!first)
        {
            cursorY +=
                node.layout.gap;
        }

        first = false;

        const auto size =
            child.desiredSize;

        Api::Rect childRect{
            x,
            cursorY,
            width,
            size.height
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        LayoutEngine::Arrange(childCtx);

        cursorY += size.height;
    }
}

} // namespace Blade

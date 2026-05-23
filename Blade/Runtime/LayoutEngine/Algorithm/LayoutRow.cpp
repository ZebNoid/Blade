#include "LayoutRow.h"

#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutRow::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    int totalWidth = 0;
    int maxHeight = 0;

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
            totalWidth +=
                node.layout.gap;
        }

        first = false;

        totalWidth +=
            size.width;

        maxHeight = max(
            maxHeight,
            size.height
        );
    }

    const auto& padding =
        node.layout.box.padding;

    node.desiredSize = {
        totalWidth +
        padding.left +
        padding.right,

        maxHeight +
        padding.top +
        padding.bottom
    };

    return node.desiredSize;
}

auto LayoutRow::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto& padding =
        node.layout.box.padding;

    int cursorX =
        ctx.rect.x + padding.left;

    const int y =
        ctx.rect.y + padding.top;

    const int height =
        ctx.rect.height -
        padding.top -
        padding.bottom;

    bool first = true;

    for (auto& child : node.children)
    {
        if (!first)
        {
            cursorX +=
                node.layout.gap;
        }

        first = false;

        const auto size =
            child.desiredSize;

        Api::Rect childRect{
            cursorX,
            y,
            size.width,
            height
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        LayoutEngine::Arrange(childCtx);

        cursorX += size.width;
    }
}

} // namespace Blade

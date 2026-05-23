#include "LayoutEngine.h"


namespace Blade {


auto LayoutEngine::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    switch (node.layoutType)
    {
    case LayoutType::Column:
        return MeasureColumn(ctx);

    // case LayoutType::Row:
    //     return MeasureRow(ctx);
    //
    // case LayoutType::Stack:
    //     return MeasureStack(ctx);

    case LayoutType::None:
    default:
        return MeasureLeaf(ctx);
    }
}

auto LayoutEngine::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    node.rect = ctx.rect;

    switch (node.layoutType)
    {
    case LayoutType::Column:
        ArrangeColumn(ctx);
        break;

    // case LayoutType::Row:
    //     ArrangeRow(ctx);
    //     break;
    //
    // case LayoutType::Stack:
    //     ArrangeStack(ctx);
    //     break;

    default:
        break;
    }
}

auto LayoutEngine::MeasureLeaf(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    // temporary stub

    node.desiredSize = {
        100,
        30
    };

    return node.desiredSize;
}

auto LayoutEngine::MeasureColumn(
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
        node.layout.layout.padding;

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

auto LayoutEngine::ArrangeColumn(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto& padding =
        node.layout.layout.padding;

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

        Arrange(childCtx);

        cursorY += size.height;
    }
}

} // namespace

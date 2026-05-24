#include "LayoutColumn.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
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

        const auto marginSize =
            LayoutGeometry::Inflate(
                size,
                child.layout.box.margin
            );

        if (!first)
        {
            totalHeight +=
                node.layout.gap;
        }

        first = false;

        maxWidth = max(
            maxWidth,
            marginSize.width
        );

        totalHeight +=
            marginSize.height;
    }

    node.desiredSize =
        LayoutGeometry::Inflate(
            {
                maxWidth,
                totalHeight
            },
            node.layout.box.padding
        );

    return node.desiredSize;
}

auto LayoutColumn::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto contentRect =
        LayoutGeometry::Deflate(
            ctx.rect,
            node.layout.box.padding
        );

    int contentHeight = 0;
    int totalFlex = 0;

    bool first = true;

    for (const auto& child : node.children)
    {
        if (!first)
        {
            contentHeight +=
                node.layout.gap;
        }

        first = false;

        contentHeight +=
            child.layout.box.margin.top +
            (child.layout.box.flex > 0 ? 0 : child.desiredSize.height) +
            child.layout.box.margin.bottom;

        totalFlex += LayoutGeometry::NonNegative(child.layout.box.flex);
    }

    const int flexSpace = totalFlex > 0 ? LayoutGeometry::NonNegative(contentRect.height - contentHeight) : 0;
    contentHeight += totalFlex > 0 ? flexSpace : 0;

    const int itemCount =
        static_cast<int>(
            node.children.size()
        );

    const int itemGap =
        LayoutGeometry::MainAxisGap(
            node.layout.mainAxisAlignment,
            node.layout.gap,
            contentRect.height,
            contentHeight,
            itemCount
        );

    int cursorY =
        contentRect.y +
        LayoutGeometry::MainAxisOffset(
            node.layout.mainAxisAlignment,
            contentRect.height,
            contentHeight,
            itemCount
        );

    first = true;

    for (auto& child : node.children)
    {
        if (!first)
        {
            cursorY +=
                itemGap;
        }

        first = false;

        const auto& margin =
            child.layout.box.margin;

        const int flex = LayoutGeometry::NonNegative(child.layout.box.flex);
        const int childHeight = totalFlex > 0 && flex > 0
            ? flexSpace * flex / totalFlex
            : child.desiredSize.height;

        cursorY +=
            margin.top;

        int childX =
            contentRect.x +
            margin.left;

        int childWidth =
            child.desiredSize.width;

        const int crossWidth =
            LayoutGeometry::NonNegative(
                contentRect.width -
                margin.left -
                margin.right
            );

        switch (node.layout.crossAxisAlignment)
        {
        case CrossAxisAlignment::Center:
            childX =
                contentRect.x +
                margin.left +
                LayoutGeometry::NonNegative(
                    crossWidth -
                    child.desiredSize.width
                ) / 2;
            break;

        case CrossAxisAlignment::End:
            childX =
                contentRect.x +
                contentRect.width -
                margin.right -
                child.desiredSize.width;
            break;

        case CrossAxisAlignment::Stretch:
            childWidth = crossWidth;
            break;

        case CrossAxisAlignment::Start:
        default:
            break;
        }

        Api::Rect childRect{
            childX,

            cursorY,

            childWidth,

            childHeight
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        LayoutEngine::Arrange(childCtx);

        cursorY += childHeight;
        cursorY += margin.bottom;
    }
}

} // namespace Blade

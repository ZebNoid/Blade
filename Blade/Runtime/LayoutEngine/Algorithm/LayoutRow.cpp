#include "LayoutRow.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
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

        const auto marginSize =
            LayoutGeometry::Inflate(
                size,
                child.layout.box.margin
            );

        if (!first)
        {
            totalWidth +=
                node.layout.gap;
        }

        first = false;

        totalWidth +=
            marginSize.width;

        maxHeight = max(
            maxHeight,
            marginSize.height
        );
    }

    node.desiredSize =
        LayoutGeometry::Inflate(
            {
                totalWidth,
                maxHeight
            },
            node.layout.box.padding
        );

    return node.desiredSize;
}

auto LayoutRow::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto contentRect =
        LayoutGeometry::Deflate(
            ctx.rect,
            node.layout.box.padding
        );

    int contentWidth = 0;

    bool first = true;

    for (const auto& child : node.children)
    {
        if (!first)
        {
            contentWidth +=
                node.layout.gap;
        }

        first = false;

        contentWidth +=
            child.layout.box.margin.left +
            child.desiredSize.width +
            child.layout.box.margin.right;
    }

    const int itemCount =
        static_cast<int>(
            node.children.size()
        );

    const int itemGap =
        LayoutGeometry::MainAxisGap(
            node.layout.mainAxisAlignment,
            node.layout.gap,
            contentRect.width,
            contentWidth,
            itemCount
        );

    int cursorX =
        contentRect.x +
        LayoutGeometry::MainAxisOffset(
            node.layout.mainAxisAlignment,
            contentRect.width,
            contentWidth,
            itemCount
        );

    first = true;

    for (auto& child : node.children)
    {
        if (!first)
        {
            cursorX +=
                itemGap;
        }

        first = false;

        const auto size =
            child.desiredSize;

        const auto& margin =
            child.layout.box.margin;

        cursorX +=
            margin.left;

        int childY =
            contentRect.y +
            margin.top;

        int childHeight =
            size.height;

        const int crossHeight =
            LayoutGeometry::NonNegative(
                contentRect.height -
                margin.top -
                margin.bottom
            );

        switch (node.layout.crossAxisAlignment)
        {
        case CrossAxisAlignment::Center:
            childY =
                contentRect.y +
                margin.top +
                LayoutGeometry::NonNegative(
                    crossHeight -
                    size.height
                ) / 2;
            break;

        case CrossAxisAlignment::End:
            childY =
                contentRect.y +
                contentRect.height -
                margin.bottom -
                size.height;
            break;

        case CrossAxisAlignment::Stretch:
            childHeight = crossHeight;
            break;

        case CrossAxisAlignment::Start:
        default:
            break;
        }

        Api::Rect childRect{
            cursorX,

            childY,

            size.width,

            childHeight
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        LayoutEngine::Arrange(childCtx);

        cursorX += size.width;
        cursorX += margin.right;
    }
}

} // namespace Blade

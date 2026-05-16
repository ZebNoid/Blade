#include "FlexLayout.h"


namespace Blade {

// -------------------------------------------------
// By LLM
// -------------------------------------------------

auto FlexLayout::Measure(
    const FlexDirection direction,
    const std::vector<std::unique_ptr<Widget>>& children,
    const LayoutProps& layout,
    const int gap,
    const Size available
) -> Size
{
    int mainSize = 0;
    int crossSize = 0;

    bool first = true;

    for (const auto& child : children)
    {
        const Size childSize =
            child->measure(available);

        const auto& margin =
            child->layout().margin;

        // gap between items
        if (!first)
        {
            mainSize += gap;
        }
        else
        {
            first = false;
        }

        if (direction == FlexDirection::Column)
        {
            mainSize +=
                margin.top +
                childSize.height +
                margin.bottom;

            crossSize = max(
                crossSize,
                margin.left +
                childSize.width +
                margin.right
            );
        }
        else // Row
        {
            mainSize +=
                margin.left +
                childSize.width +
                margin.right;

            crossSize = max(
                crossSize,
                margin.top +
                childSize.height +
                margin.bottom
            );
        }
    }

    // apply container padding
    mainSize +=
        layout.padding.top +
        layout.padding.bottom;

    crossSize +=
        layout.padding.left +
        layout.padding.right;

    if (direction == FlexDirection::Column)
    {
        return {
            crossSize,
            mainSize
        };
    }

    return {
        mainSize,
        crossSize
    };
}

auto FlexLayout::Arrange(
    const FlexDirection direction,
    const std::vector<std::unique_ptr<Widget>>& children,
    const LayoutProps& layout,
    const MainAxisAlignment mainAxisAlignment,
    const CrossAxisAlignment crossAxisAlignment,
    const int gap,
    const Rect rect
) -> void
{
    // -------------------------------------------------
    // Content rect after padding
    // -------------------------------------------------

    const Rect contentRect = {
        rect.x + layout.padding.left,
        rect.y + layout.padding.top,

        rect.width
            - layout.padding.left
            - layout.padding.right,

        rect.height
            - layout.padding.top
            - layout.padding.bottom
    };

    // -------------------------------------------------
    // Pass 1:
    // calculate fixed size + total flex
    // -------------------------------------------------

    int fixedMainSize = 0;
    int totalFlex = 0;

    bool first = true;

    for (const auto& child : children)
    {
        const auto& childLayout =
            child->layout();

        const auto& margin =
            childLayout.margin;

        if (!first)
        {
            fixedMainSize += gap;
        }
        else
        {
            first = false;
        }

        if (childLayout.flex > 0)
        {
            totalFlex += childLayout.flex;

            // margins still consume space
            if (direction == FlexDirection::Column)
            {
                fixedMainSize +=
                    margin.top +
                    margin.bottom;
            }
            else
            {
                fixedMainSize +=
                    margin.left +
                    margin.right;
            }

            continue;
        }

        const Size childSize =
            child->measure({
                contentRect.width,
                contentRect.height
            });

        if (direction == FlexDirection::Column)
        {
            fixedMainSize +=
                margin.top +
                childSize.height +
                margin.bottom;
        }
        else
        {
            fixedMainSize +=
                margin.left +
                childSize.width +
                margin.right;
        }
    }

    // -------------------------------------------------
    // Remaining free space
    // -------------------------------------------------

    const int availableMainSize =
        (direction == FlexDirection::Column)
            ? contentRect.height
            : contentRect.width;

    int remainingMainSize =
        availableMainSize - fixedMainSize;

    if (remainingMainSize < 0)
    {
        remainingMainSize = 0;
    }

    // -------------------------------------------------
    // Calculate final content size
    // (needed for alignment)
    // -------------------------------------------------

    int contentMainSize = fixedMainSize;

    if (totalFlex > 0)
    {
        contentMainSize += remainingMainSize;
    }

    // -------------------------------------------------
    // Main axis start position
    // -------------------------------------------------

    int cursor =
        (direction == FlexDirection::Column)
            ? contentRect.y
            : contentRect.x;

    switch (mainAxisAlignment)
    {
        case MainAxisAlignment::Center:
        {
            cursor +=
                (availableMainSize - contentMainSize) / 2;
            break;
        }

        case MainAxisAlignment::End:
        {
            cursor +=
                availableMainSize - contentMainSize;
            break;
        }

        case MainAxisAlignment::Start:
        default:
            break;
    }

    // -------------------------------------------------
    // Pass 2:
    // arrange children
    // -------------------------------------------------

    first = true;

    for (const auto& child : children)
    {
        const auto& childLayout =
            child->layout();

        const auto& margin =
            childLayout.margin;

        if (!first)
        {
            cursor += gap;
        }
        else
        {
            first = false;
        }

        Size childSize =
            child->measure({
                contentRect.width,
                contentRect.height
            });

        // ---------------------------------------------
        // Apply flex
        // ---------------------------------------------

        if (childLayout.flex > 0 && totalFlex > 0)
        {
            const int flexSize =
                remainingMainSize *
                childLayout.flex /
                totalFlex;

            if (direction == FlexDirection::Column)
            {
                childSize.height = flexSize;
            }
            else
            {
                childSize.width = flexSize;
            }
        }

        int x = contentRect.x;
        int y = contentRect.y;

        int width = childSize.width;
        int height = childSize.height;

        // =================================================
        // COLUMN
        // =================================================

        if (direction == FlexDirection::Column)
        {
            cursor += margin.top;

            switch (crossAxisAlignment)
            {
                case CrossAxisAlignment::Center:
                {
                    x +=
                        (contentRect.width - childSize.width) / 2;
                    break;
                }

                case CrossAxisAlignment::End:
                {
                    x +=
                        contentRect.width -
                        childSize.width -
                        margin.right;
                    break;
                }

                case CrossAxisAlignment::Stretch:
                {
                    width =
                        contentRect.width -
                        margin.left -
                        margin.right;

                    x += margin.left;

                    break;
                }

                case CrossAxisAlignment::Start:
                default:
                {
                    x += margin.left;
                    break;
                }
            }

            y = cursor;

            child->arrange({
                x,
                y,
                width,
                height
            });

            cursor += height;
            cursor += margin.bottom;
        }

        // =================================================
        // ROW
        // =================================================

        else
        {
            cursor += margin.left;

            switch (crossAxisAlignment)
            {
                case CrossAxisAlignment::Center:
                {
                    y +=
                        (contentRect.height - childSize.height) / 2;
                    break;
                }

                case CrossAxisAlignment::End:
                {
                    y +=
                        contentRect.height -
                        childSize.height -
                        margin.bottom;
                    break;
                }

                case CrossAxisAlignment::Stretch:
                {
                    height =
                        contentRect.height -
                        margin.top -
                        margin.bottom;

                    y += margin.top;

                    break;
                }

                case CrossAxisAlignment::Start:
                default:
                {
                    y += margin.top;
                    break;
                }
            }

            x = cursor;

            child->arrange({
                x,
                y,
                width,
                height
            });

            cursor += width;
            cursor += margin.right;
        }
    }
}


} // namespace

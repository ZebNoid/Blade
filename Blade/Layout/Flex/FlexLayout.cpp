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
    // Calculate content main size
    // -------------------------------------------------

    int contentMainSize = 0;

    bool first = true;

    for (const auto& child : children)
    {
        const Size childSize =
            child->measure({
                contentRect.width,
                contentRect.height
            });

        const auto& margin =
            child->layout().margin;

        if (!first)
        {
            contentMainSize += gap;
        }
        else
        {
            first = false;
        }

        if (direction == FlexDirection::Column)
        {
            contentMainSize +=
                margin.top +
                childSize.height +
                margin.bottom;
        }
        else
        {
            contentMainSize +=
                margin.left +
                childSize.width +
                margin.right;
        }
    }

    // -------------------------------------------------
    // Main axis start position
    // -------------------------------------------------

    int cursor =
        (direction == FlexDirection::Column)
            ? contentRect.y
            : contentRect.x;

    const int availableMainSize =
        (direction == FlexDirection::Column)
            ? contentRect.height
            : contentRect.width;

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
    // Arrange children
    // -------------------------------------------------

    first = true;

    for (const auto& child : children)
    {
        const Size childSize =
            child->measure({
                contentRect.width,
                contentRect.height
            });

        const auto& margin =
            child->layout().margin;

        if (!first)
        {
            cursor += gap;
        }
        else
        {
            first = false;
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

            // ---------------------------------------------
            // Cross axis alignment
            // ---------------------------------------------

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

            // ---------------------------------------------
            // Cross axis alignment
            // ---------------------------------------------

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

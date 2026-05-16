#include "Column.h"

auto Column::measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    const int spacing = m_props.spacing;
    bool first = true;

    for (const auto& child : m_children)
    {
        Size s = child->measure(available);

        // spacing between items
        if (!first)
        {
            totalHeight += spacing;
        }

        const auto& margin = child->layout().margin;

        totalHeight +=
            margin.top +
            s.height +
            margin.bottom;

        maxWidth = max(
            maxWidth,
            margin.left +
            s.width +
            margin.right
        );

        first = false;

        // totalHeight += s.height;
        // maxWidth = max(maxWidth, s.width);
    }

    return {
        maxWidth,
        totalHeight
    };
}

auto Column::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    int y = rect.y;

    for (const auto& child : m_children)
    {
        Size size = child->measure({rect.width, rect.height});
        const auto& margin = child->layout().margin;

        y += margin.top;

        child->arrange({
            rect.x + margin.left,
            y,
            rect.width - margin.left - margin.right,
            size.height
        });

        y += size.height;
        y += margin.bottom;
    }
}

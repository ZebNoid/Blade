#include "Column.h"


namespace Blade {


auto Column::measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    const int gap = m_props.gap;
    bool first = true;

    for (const auto& child : m_children)
    {
        Size childSize = child->measure(available);
        const auto& margin = child->layout().margin;

        // spacing between items
        if (!first)
        {
            totalHeight += gap;
        }
        else
        {
            first = false;
        }

        totalHeight +=
            margin.top +
            childSize.height +
            margin.bottom;

        maxWidth = max(
            maxWidth,
            margin.left +
            childSize.width +
            margin.right
        );

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
    bool first = true;

    for (const auto& child : m_children)
    {
        // TODO later caching ?
        Size childSize = child->measure({rect.width, rect.height});
        const auto& margin = child->layout().margin;

        if (!first)
        {
            y += m_props.gap;
        }
        else
        {
            first = false;
        }

        y += margin.top;

        child->arrange({
            rect.x + margin.left,
            y,
            rect.width - margin.left - margin.right,
            childSize.height
        });

        y += childSize.height;
        y += margin.bottom;
    }
}


} // namespace

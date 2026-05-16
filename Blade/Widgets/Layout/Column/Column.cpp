#include "Column.h"

auto Column::measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    for (const auto& child : m_children)
    {
        Size s = child->measure(available);
        totalHeight += s.height;
        maxWidth = max(maxWidth, s.width);
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

        y += margin.top; // TODO

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

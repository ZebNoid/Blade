#include "Row.h"

auto Row::measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->measure(available);
        totalHeight += height;
        maxWidth = max(maxWidth, width);
    }

    return {
        maxWidth,
        totalHeight
    };
}

auto Row::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);
    int x = rect.x;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->measure({rect.width, rect.height});

        child->arrange({
            x,
            rect.y,
            width,
            rect.height
        });

        x += width;
    }
}

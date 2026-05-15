#include "Row.h"

auto Row::Measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->Measure(available);
        totalHeight += height;
        maxWidth = max(maxWidth, width);
    }

    return {
        maxWidth,
        totalHeight
    };
}

auto Row::Arrange(const Rect rect) -> void
{
    Widget::Arrange(rect);
    int x = rect.x;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->Measure({rect.width, rect.height});

        child->Arrange({
            x,
            rect.y,
            width,
            rect.height
        });

        x += width;
    }
}

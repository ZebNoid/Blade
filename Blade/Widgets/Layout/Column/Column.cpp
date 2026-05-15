#include "Column.h"

auto Column::Measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    for (const auto& child : m_children)
    {
        Size s = child->Measure(available);
        totalHeight += s.height;
        maxWidth = max(maxWidth, s.width);
    }

    return {
        maxWidth,
        totalHeight
    };
}

auto Column::Arrange(const Rect rect) -> void
{
    Widget::Arrange(rect);

    int y = rect.y;

    for (const auto& child : m_children)
    {
        Size size = child->Measure({rect.width, rect.height});

        child->Arrange({
            rect.x,
            y,
            rect.width,
            size.height
        });

        y += size.height;
    }
}

#include "Row.h"

auto Row::measure(const Size available) -> Size
{
    int totalHeight = 0;
    int maxWidth = 0;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->measure(available);

        //  TODO
        // const auto& margin = child->layout().margin;
        //
        // totalHeight +=
        //     margin.top +
        //     height +
        //     margin.bottom;
        //
        // maxWidth = max(
        //     maxWidth,
        //     margin.left +
        //     width +
        //     margin.right
        // );

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
        const auto& margin = child->layout().margin;

        x += margin.left;

        child->arrange({
            x,
            rect.y + margin.top,
            width,
            rect.height - margin.top - margin.bottom
        });

        x += width;
        x += margin.right;
    }
}

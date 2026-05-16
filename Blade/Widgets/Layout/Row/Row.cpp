#include "Row.h"


namespace Blade {


auto Row::measure(const Size available) -> Size
{
    int totalWidth = 0;
    int maxHeight = 0;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->measure(available);
        const auto& margin = child->layout().margin;

        totalWidth +=
            margin.left +
            width +
            margin.right;

        maxHeight = max(
            maxHeight,
            margin.top +
            height +
            margin.bottom
        );
    }

    return {
        totalWidth,
        maxHeight
    };
}

auto Row::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    int x = rect.x;
    bool first = true;

    for (const auto& child : m_children)
    {
        auto [width, height] = child->measure({rect.width, rect.height});
        const auto& margin = child->layout().margin;

        if (!first)
        {
            x += m_props.gap;
        }
        else
        {
            first = false;
        }

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


} // namespace

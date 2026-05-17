#include "Stack.h"


namespace Blade {


auto Stack::measure(Size available) -> Size
{
    int maxWidth = 0;
    int maxHeight = 0;

    for (const auto& child : m_children)
    {
        auto size = child->measure(available);

        maxWidth = max(maxWidth, size.width);
        maxHeight = max(maxHeight, size.height);
    }

    return {
        maxWidth,
        maxHeight
    };
}

void Stack::arrange(Rect rect)
{
    Widget::arrange(rect);

    for (const auto& child : m_children)
    {
        child->arrange(rect);
    }
}


} // namespace

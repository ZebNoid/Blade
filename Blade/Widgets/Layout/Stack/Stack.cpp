#include "Stack.h"

#include "Layout/StackLayout/StackLayout.h"


namespace Blade {


auto Stack::measure(Size available) -> Size
{
    return StackLayout::Measure(
        m_children,
        m_props.layout,
        available
    );
}

auto Stack::arrange(Rect rect) -> void
{
    Widget::arrange(rect);

    StackLayout::Arrange(
        m_children,
        m_props.layout,
        rect
    );
}


} // namespace

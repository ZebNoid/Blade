#include "Column.h"

#include "Layout/Flex/FlexLayout.h"


namespace Blade {

auto Column::measure(Size available) -> Size
{
    return FlexLayout::Measure(
        FlexDirection::Column,
        m_children,
        m_props.layout,
        m_props.gap,
        available
    );
}

auto Column::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    return FlexLayout::Arrange(
        FlexDirection::Column,
        m_children,
        m_props.layout,
        m_props.mainAxisAlignment,
        m_props.crossAxisAlignment,
        m_props.gap,
        rect
    );
}

} // namespace

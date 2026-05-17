#include "Row.h"

#include "../../../Layout/FlexLayout/FlexLayout.h"


namespace Blade {


auto Row::measure(Size available) -> Size
{
    return FlexLayout::Measure(
        FlexDirection::Row,
        m_children,
        m_props.layout,
        m_props.gap,
        available
    );
}

auto Row::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    return FlexLayout::Arrange(
        FlexDirection::Row,
        m_children,
        m_props.layout,
        m_props.mainAxisAlignment,
        m_props.crossAxisAlignment,
        m_props.gap,
        rect
    );
}

} // namespace

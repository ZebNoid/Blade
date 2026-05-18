#include "Column.h"

#include "Layout/FlexLayout/FlexLayout.h"
#include "Layout/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto Column::measure(Size available) -> Size
{
    return LayoutEngine::Measure(
        LayoutType::Flex, // LayoutContext
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

    return LayoutEngine::Arrange(
        LayoutType::Flex, // LayoutContext
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

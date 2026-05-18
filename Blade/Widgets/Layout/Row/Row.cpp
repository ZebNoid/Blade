#include "Row.h"

#include "Layout/FlexLayout/FlexLayout.h"
#include "Layout/LayoutEngine/LayoutEngine.h"


namespace Blade {


auto Row::measure(Size available) -> Size
{
    return LayoutEngine::Measure(
        LayoutType::Flex,
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

    return LayoutEngine::Arrange(
        LayoutType::Flex, // LayoutContext
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

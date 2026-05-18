#include "Column.h"

#include "Layout/LayoutFlex/LayoutFlex.h"
#include "Layout/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto Column::measure(Size available) -> Size
{
    return LayoutEngine::Measure({
        .type = LayoutType::Flex,
        .direction = FlexDirection::Column,
        .children = &m_children,
        .layout = &m_props.layout,
        .gap = m_props.gap,
        .available = available,
    });
}

auto Column::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    return LayoutEngine::Arrange({
        .type = LayoutType::Flex,
        .direction = FlexDirection::Column,
        .children = &m_children,
        .layout = &m_props.layout,
        .mainAxisAlignment = m_props.mainAxisAlignment,
        .crossAxisAlignment = m_props.crossAxisAlignment,
        .gap = m_props.gap,
        .rect = rect,
    });
}

} // namespace

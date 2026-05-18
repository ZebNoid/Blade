#include "Row.h"

#include "Layout/FlexLayout/FlexLayout.h"
#include "Layout/LayoutEngine/LayoutEngine.h"


namespace Blade {


auto Row::measure(Size available) -> Size
{
    return LayoutEngine::Measure({
        .type = LayoutType::Flex,
        .direction = FlexDirection::Row,
        .children = &m_children,
        .layout = &m_props.layout,
        .gap = m_props.gap,
        .available = available,
    });
}

auto Row::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    return LayoutEngine::Arrange({
        .type = LayoutType::Flex,
        .direction = FlexDirection::Row,
        .children = &m_children,
        .layout = &m_props.layout,
        .mainAxisAlignment = m_props.mainAxisAlignment,
        .crossAxisAlignment = m_props.crossAxisAlignment,
        .gap = m_props.gap,
        .rect = rect,
    });
}

} // namespace

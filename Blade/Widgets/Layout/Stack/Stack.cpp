#include "Stack.h"

#include "Layout/LayoutEngine/LayoutEngine.h"
#include "Layout/StackLayout/StackLayout.h"


namespace Blade {


auto Stack::measure(Size available) -> Size
{
    return LayoutEngine::Measure({
        .type = LayoutType::Stack,
        .direction = FlexDirection::Column,
        .children = &m_children,
        .layout = &m_props.layout,
        .available = available,
    });
}

auto Stack::arrange(Rect rect) -> void
{
    Widget::arrange(rect);

    return LayoutEngine::Arrange({
        .type = LayoutType::Stack,
        .direction = FlexDirection::Column,
        .children = &m_children,
        .layout = &m_props.layout,
        .rect = rect,
    });
}


} // namespace

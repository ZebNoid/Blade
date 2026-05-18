#include "Stack.h"

#include "Layout/LayoutEngine/LayoutEngine.h"
#include "Layout/StackLayout/StackLayout.h"


namespace Blade {


auto Stack::measure(Size available) -> Size
{
    return LayoutEngine::Measure(
        LayoutType::Stack,
        FlexDirection::Row,
        m_children,
        m_props.layout,
        0, // NO gap // note used here
        available
    );
}

auto Stack::arrange(Rect rect) -> void
{
    Widget::arrange(rect);

    return LayoutEngine::Arrange(
        LayoutType::Stack, // LayoutContext
        FlexDirection::Row,
        m_children,
        m_props.layout,
        MainAxisAlignment::Center, // note used here
        CrossAxisAlignment::Center, // note used here
        0, // note used here
        rect
    );

    StackLayout::Arrange(
        m_children,
        m_props.layout,
        rect
    );
}


} // namespace

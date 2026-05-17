#include "Stack.h"


namespace Blade {


auto Stack::measure(Size available) -> Size
{
    int maxWidth = 0;
    int maxHeight = 0;

    const auto& padding = m_props.layout.padding;

    for (const auto& child : m_children)
    {
        auto size = child->measure(available);

        const auto& margin =
            child->layout().margin;

        maxWidth = max(
            maxWidth,
            margin.left +
            size.width +
            margin.right
        );

        maxHeight = max(
            maxHeight,
            margin.top +
            size.height +
            margin.bottom
        );
    }

    return {
        maxWidth + padding.left + padding.right,
        maxHeight + padding.top + padding.bottom
    };
}

auto Stack::arrange(Rect rect)
    -> void
{
    Widget::arrange(rect);

    const auto& padding =
        m_props.layout.padding;

    Rect contentRect{
        rect.x + padding.left,
        rect.y + padding.top,
        rect.width -
            padding.left -
            padding.right,
        rect.height -
            padding.top -
            padding.bottom
    };

    for (const auto& child : m_children)
    {
        const auto& margin =
            child->layout().margin;

        child->arrange({
            contentRect.x + margin.left,
            contentRect.y + margin.top,

            contentRect.width -
                margin.left -
                margin.right,

            contentRect.height -
                margin.top -
                margin.bottom
        });
    }
}


    // auto updateZOrder() -> void;
// auto Stack::updateZOrder() -> void
// {
    // HWND previous = nullptr;
    //
    // for (auto it = m_children.rbegin();         it != m_children.rend();         ++it)
    // {
    //     auto hwnd = (*it)->nativeHandle();
    //
    //     SetWindowPos(
    //         hwnd,
    //         previous,
    //         0,
    //         0,
    //         0,
    //         0,
    //         SWP_NOMOVE |
    //         SWP_NOSIZE |
    //         SWP_NOACTIVATE
    //     );
    //
    //     previous = hwnd;
    // }
// }


} // namespace

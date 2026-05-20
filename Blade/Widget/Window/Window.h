#pragma once
#include "Widget/Widget.h"
#include "WidgetNode/WidgetNode.h"


namespace Blade {


class Window
{
public:
    Window() = default;

    template <typename... TWidgets>
    Window(TWidgets&&... widgets)
    {
        (m_children.add(std::forward<TWidgets>(widgets)), ...);
    }

    auto buildTree() const -> Api::WidgetTree
    {
        return m_children.tree();
    }

private:
    WidgetNode m_children;
};


} // namespace

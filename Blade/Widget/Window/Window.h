#pragma once

#include <optional>

#include "WindowProps.h"
#include "WindowEvents.h"
#include "Widget/Widget.h"
#include "WidgetNode/WidgetNode.h"


namespace Blade {

class Window : public Widget
{
public:
    Window()
    {
        m_tree.type = L"Window";
    }

    explicit Window(Widget child)
    {
        m_tree.type = L"Window";
        m_tree.children.push_back(child.buildTree());
    }

    auto set(WindowProps props) -> Window&
    {
        m_tree.props = std::move(props);
        return *this;
    }

    auto on(WindowEvents events) -> Window&
    {
        m_tree.events = std::move(events);
        return *this;
    }

};


} // namespace

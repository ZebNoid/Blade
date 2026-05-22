#pragma once

#include "WindowProps.h"
#include "WindowEvents.h"
#include "Base/RootWidget.h"
#include "Runtime/Normalize/Normalize.h"


namespace Blade {

class Window : public RootWidget
{
public:
    Window()
    {
        m_tree.type = Window::type();
    }

    explicit Window(Widget child)
    {
        m_tree.type = Window::type();
        m_tree.children.push_back(child.buildTree());
    }

    auto type() const -> Api::Text override
    {
        return L"Window";
    }

    auto set(WindowProps props) -> Window&
    {
        m_tree.props = Normalize::Props(props);
        return *this;
    }

    auto on(WindowEvents events) -> Window&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};


} // namespace

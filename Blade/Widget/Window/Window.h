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
        m_tree.type = L"Window";
        Normalize::PropsMerge(m_tree, WindowProps{});
    }

    explicit Window(const Widget& child)
    {
        m_tree.type = L"Window";
        Normalize::PropsMerge(m_tree, WindowProps{});

        m_tree.children.push_back(
            child.tree()
        );
    }

    auto set(WindowProps props) -> Window&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto on(WindowEvents events) -> Window&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};


} // namespace

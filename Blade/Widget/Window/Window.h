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
        m_tree.props = Normalize::Props(WindowProps{});
    }

    explicit Window(const Widget& child)
    {
        m_tree.type = L"Window";
        m_tree.props = Normalize::Props(WindowProps{});

        m_tree.children.push_back(
            child.tree()
        );
    }

    auto set(WindowProps props) -> Window&
    {
        auto normalized = Normalize::Props(props);
        for (auto& [key, value] : normalized)
        {
            m_tree.props.insert_or_assign(key, std::move(value));
        }
        return *this;
    }

    auto on(WindowEvents events) -> Window&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};


} // namespace

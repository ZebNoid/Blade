#pragma once

#include "ButtonProps.h"
#include "ButtonEvents.h"
#include "Widget/Widget.h"


namespace Blade {

class Button : public Widget
{
public:
    Button(Api::Text text)
    {
        m_tree.type = L"Button";
        m_tree.custom = std::move(text);
    }

    auto set(ButtonProps props) -> Button&
    {
        m_tree.props = std::move(props);
        return *this;
    }

    auto on(ButtonEvents events) -> Button&
    {
        m_tree.events = std::move(events);
        return *this;
    }
};

} // namespace

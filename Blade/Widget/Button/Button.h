#pragma once

#include "ButtonProps.h"
#include "ButtonEvents.h"
#include "Runtime/Normalize/Normalize.h"
#include "Base/Widget.h"


namespace Blade {

class Button : public Widget
{
public:
    explicit Button(Api::Text text)
    {
        m_tree.type = L"Button";
        m_tree.props = Normalize::Props(ButtonProps{});
        m_tree.props[Api::Props::Title] = std::move(text);
    }

    auto set(ButtonProps props) -> Button&
    {
        auto normalized = Normalize::Props(props);
        for (auto& [key, value] : normalized)
        {
            m_tree.props.insert_or_assign(key, std::move(value));
        }
        return *this;
    }

    auto on(ButtonEvents events) -> Button&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};

} // namespace

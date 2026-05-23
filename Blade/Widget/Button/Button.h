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
        Normalize::PropsMerge(m_tree, ButtonProps{});
        m_tree.backend.create[Api::Props::Title] = std::move(text);
    }

    auto set(ButtonProps props) -> Button&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto on(ButtonEvents events) -> Button&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};

} // namespace

#pragma once

#include "ButtonProps.h"
#include "ButtonEvents.h"
#include "Runtime/Normalize/Normalize.h"
#include "Base/Widget.h"


namespace Blade {

class Button : public Widget<Button>
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

    auto defaultButton(bool value = true) -> Button&
    {
        m_tree.backend.create[Api::Props::IsDefault] = value;
        return *this;
    }

    auto onClick(Api::EventCallback callback) -> Button&
    {
        applyEvent(Api::Events::Click, std::move(callback));
        return *this;
    }

    auto onFocus(Api::EventCallback callback) -> Button&
    {
        applyEvent(Api::Events::Focus, std::move(callback));
        return *this;
    }

    auto onDrop(Api::EventCallback callback) -> Button&
    {
        applyEvent(Api::Events::Drop, std::move(callback));
        return *this;
    }
};

} // namespace

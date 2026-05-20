#pragma once

#include "ButtonProps.h"
#include "ButtonEvents.h"
#include "Mixin/EventMixin.h"
#include "Mixin/PropsMixin.h"
#include "Widget/Widget.h"


namespace Blade {


class Button : public Widget
{
public:
    Button(Api::Text text)
        : m_text(std::move(text))
    {
    }

    auto set(ButtonProps props) -> Button&
    {
        m_props = std::move(props);
        return *this;
    }

    auto on(ButtonEvents events) -> Button&
    {
        m_events = std::move(events);
        return *this;
    }

    auto type() const -> Api::Text override { return L"Button"; }

    auto buildTree() const -> Api::WidgetTree override;

private:
    Api::Text m_text;
    ButtonProps m_props{};
    ButtonEvents m_events{};
};

} // namespace

#pragma once

#include "ButtonProps.h"
#include "ButtonEvents.h"
#include "Mixin/EventMixin.h"
#include "Mixin/PropsMixin.h"
#include "Widget/Widget.h"


namespace Blade {


class Button
    : public Widget
      , public PropsMixin<Button>
      , public EventMixin<Button>
{
public:
    Button(Api::Text text)
        : m_text(std::move(text))
    {
    }

    void applyProp(ButtonProps props) {}
    void addHandler(ButtonEvents events) {}

    auto type() const -> Api::Text override;

    auto buildTree() const -> Api::WidgetTree override;

private:
    Api::Text m_text;
};

} // namespace

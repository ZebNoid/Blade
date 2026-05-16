#pragma once

#include "Backend/NativeButton/NativeButton.h"
#include "Props/Widget/ButtonProps.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class Button : public Widget
{
public:
    Button(std::string text);

    // lvalue
    auto onClick(std::function<void()> fn) & -> Button&
    {
        m_onClick = std::move(fn);
        return *this;
    }

    // rvalue
    auto onClick(std::function<void()> fn) && -> Button&&
    {
        m_onClick = std::move(fn);
        return std::move(*this);
    }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto measure(Size available) -> Size override
    {
        return {140, 40};
    }

    auto arrange(Rect rect) -> void override
    {
        Widget::arrange(rect);

        m_native.setRect(rect);
    }

    auto set(ButtonProps props) -> Button&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto id(WidgetId& id) -> Button&
    {
        id = m_id;
        return *this;
    }

private:
    NativeButton m_native;
    ButtonProps m_props;

    std::string m_text;
    std::function<void()> m_onClick;
};


} // namespace

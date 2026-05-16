#pragma once

#include "Widgets/Widget/Widget.h"
#include "Native/NativeButton/NativeButton.h"
#include "Props/Widget/ButtonProps.h"

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

private:
    NativeButton m_native;
    std::string m_text;
    std::function<void()> m_onClick;
    ButtonProps m_props;

    friend class Materializer;
};

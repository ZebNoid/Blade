#pragma once

#include "Backend/NativeTextField/NativeTextField.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class TextField : public Widget
{
public:
    TextField();

    // lvalue
    auto onChange(std::function<void(std::string)> fn) & -> TextField&
    {
        m_onChange = std::move(fn);
        return *this;
    }

    // rvalue
    auto onChange(std::function<void(std::string)> fn) && -> TextField&&
    {
        m_onChange = std::move(fn);
        return std::move(*this);
    }


    // lvalue
    auto onFocus(std::function<void(bool)> fn) & -> TextField&
    {
        m_onFocus = std::move(fn);
        return *this;
    }

    // rvalue
    auto onFocus(std::function<void(bool)> fn) && -> TextField&&
    {
        m_onFocus = std::move(fn);
        return std::move(*this);
    }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto measure(Size available) -> Size override
    {
        return {140, 40}; // TODO size property
    }

    auto arrange(Rect rect) -> void override
    {
        Widget::arrange(rect);

        m_native.setRect(rect);
    }

private:
    NativeTextField m_native;
    std::function<void(std::string)> m_onChange;
    std::function<void(bool)> m_onFocus;
};


} // namespace

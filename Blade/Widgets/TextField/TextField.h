#pragma once

#include "../Widget/Widget.h"
#include "../../Native/NativeTextField/NativeTextField.h"

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

    auto Mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto Measure(Size available) -> Size override
    {
        return {140, 40}; // TODO size property
    }

    auto Arrange(Rect rect) -> void override
    {
        Widget::Arrange(rect);

        m_native.SetRect(rect);
    }

private:
    NativeTextField m_native;
    std::function<void(std::string)> m_onChange;
    std::function<void(bool)> m_onFocus;
};

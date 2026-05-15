#pragma once

#include "../Widget/Widget.h"
#include "../../Native/NativeButton/NativeButton.h"

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

    auto Mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto Measure(Size available) -> Size override
    {
        return {140, 40};
    }

    auto Arrange(Rect rect) -> void override
    {
        Widget::Arrange(rect);

        m_native.SetRect(rect);
    }

private:
    NativeButton m_native;
    std::string m_text;
    std::function<void()> m_onClick;

    friend class Materializer;
};

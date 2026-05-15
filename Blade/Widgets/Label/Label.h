#pragma once

#include "../Widget/Widget.h"
#include "../../Native/NativeLabel/NativeLabel.h"

class Label : public Widget
{
public:
    Label(std::string text);

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
    NativeLabel m_native;

    std::string m_text;
};

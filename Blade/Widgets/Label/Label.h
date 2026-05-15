#pragma once

#include "../Widget/Widget.h"
#include "../../Native/NativeLabel/NativeLabel.h"

class Label : public Widget
{
public:
    Label(std::string text);

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

private:
    NativeLabel m_native;

    std::string m_text;
};

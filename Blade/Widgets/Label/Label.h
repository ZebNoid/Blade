#pragma once

#include "Widgets/Widget/Widget.h"
#include "Native/NativeLabel/NativeLabel.h"
#include "Props/Widget/LabelProps.h"

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

    auto set(LabelProps props) -> Label&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

private:
    NativeLabel m_native;

    std::string m_text;

    LabelProps m_props;
};

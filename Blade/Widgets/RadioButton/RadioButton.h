#pragma once

#include "Backend/NativeRadioButton/NativeRadioButton.h"
#include "WidgetsProps/Widget/RadioButtonProps.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class RadioButton : public Widget
{
public:
    RadioButton(std::string text);

    auto name() -> std::wstring override { return L"RadioButton"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto measure(Size available) -> Size override
    {
        return {140, 20};
    }

    auto arrange(Rect rect) -> void override
    {
        Widget::arrange(rect);

        m_native.setRect(rect);
    }

    auto set(RadioButtonProps props) -> RadioButton&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto id(WidgetId& id) -> RadioButton&
    {
        id = m_id;
        return *this;
    }

private:
    NativeRadioButton m_native;
    RadioButtonProps m_props;

    std::string m_text;
};


} // namespace

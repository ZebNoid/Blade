#pragma once

#include "Backend/NativeTextField/NativeTextField.h"
#include "WidgetsProps/Widget/TextFieldProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsEvents/Widget/TextFieldEvents.h"


namespace Blade {


class TextField : public Widget
{
public:
    TextField(const std::string& text = "");

    auto name() -> std::wstring override { return L"TextField"; }

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

    auto set(TextFieldProps props) -> TextField&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto on(TextFieldEvents events) -> TextField&
    {
        m_events = std::move(events);
        return *this;
    }

    auto id(WidgetId& id) -> TextField&
    {
        id = m_id;
        return *this;
    }

private:
    NativeTextField m_native;
    TextFieldProps m_props;
    TextFieldEvents m_events;
    std::string m_text;
};


} // namespace

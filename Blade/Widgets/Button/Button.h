#pragma once

#include "Backend/NativeButton/NativeButton.h"
#include "WidgetsProps/Widget/ButtonProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsCallbacks/Widget/ButtonCallbacks.h"


namespace Blade {


class Button : public Widget
{
public:
    Button(std::string text);

    auto name() -> std::wstring override { return L"Button"; }

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

    auto on(ButtonCallbacks callbacks) -> Button&
    {
        m_callbacks = std::move(callbacks);
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
    ButtonCallbacks m_callbacks;

    std::string m_text;
};


} // namespace

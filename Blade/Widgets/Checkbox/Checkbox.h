#pragma once

#include "Backend/NativeCheckbox/NativeCheckbox.h"
#include "WidgetsProps/Widget/CheckboxProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsCallbacks/Widget/CheckboxCallbacks.h"


namespace Blade {


class Checkbox : public Widget
{
public:
    Checkbox(std::string text);

    auto name() -> std::wstring override  { return L"Checkbox"; }

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

    auto set(CheckboxProps props) -> Checkbox&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto on(CheckboxCallbacks callbacks) -> Checkbox&
    {
        m_callbacks = std::move(callbacks);
        return *this;
    }

    auto id(WidgetId& id) -> Checkbox&
    {
        id = m_id;
        return *this;
    }

private:
    NativeCheckbox m_native;
    CheckboxProps m_props;
    CheckboxCallbacks m_callbacks;

    std::string m_text;
};


} // namespace

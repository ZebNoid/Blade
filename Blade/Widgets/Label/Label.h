#pragma once

#include "Backend/NativeLabel/NativeLabel.h"
#include "Props/Widget/LabelProps.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class Label : public Widget
{
public:
    Label(std::string text);

    auto name() -> std::wstring override { return L"Label"; }

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

    auto id(WidgetId& id) -> Label&
    {
        id = m_id;
        return *this;
    }

private:
    NativeLabel m_native;
    LabelProps m_props;

    std::string m_text;
};


} // namespace

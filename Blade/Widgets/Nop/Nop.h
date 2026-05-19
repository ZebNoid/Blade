#pragma once

#include "Widgets/Widget/Widget.h"
#include "WidgetsProps/Widget/NopProps.h"


namespace Blade {


class Nop : public Widget
{
public:
    Nop(std::string text = "Nop");

    auto name() -> std::wstring override { return L"Nop"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto measure(Size available) -> Size override
    {
        return {140, 40};
    }

    auto arrange(Rect rect) -> void override
    {
        Widget::arrange(rect);
        // m_native.setRect(rect);
    }

    auto set(NopProps props) -> Nop&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto id(WidgetId& id) -> Nop&
    {
        id = m_id;
        return *this;
    }

private:
    // NativeNop m_native;
    NopProps m_props;

    std::string m_text;
};


} // namespace

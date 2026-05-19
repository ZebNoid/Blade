#pragma once

#include "WidgetsProps/Widget/ProgressProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsEvents/Widget/ProgressEvents.h"


namespace Blade {


class Progress : public Widget
{
public:
    Progress(int value);

    auto name() -> std::wstring override { return L"Progress"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto measure(Size available) -> Size override
    {
        // TODO default size
        return {140, 40};
    }

    auto arrange(Rect rect) -> void override
    {
        Widget::arrange(rect);
        // m_native.setRect(rect);
    }

    auto set(ProgressProps props) -> Progress&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto on(ProgressEvents events) -> Progress&
    {
        m_events = std::move(events);
        return *this;
    }

    auto id(WidgetId& id) -> Progress&
    {
        id = m_id;
        return *this;
    }

private:
    // NativeProgress m_native;
    ProgressProps m_props;
    ProgressEvents m_events;

    int m_value;
};


} // namespace

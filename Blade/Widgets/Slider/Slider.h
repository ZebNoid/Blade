#pragma once

#include "Backend/NativeSlider/NativeSlider.h"
#include "WidgetsProps/Widget/SliderProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsEvents/Widget/SliderEvents.h"


namespace Blade {


class Slider : public Widget
{
public:
    Slider(int value);

    auto name() -> std::wstring override  { return L"Slider"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override;

    auto measure(Size available) -> Size override
    {
        // TODO default size
        return {140, 40};
    }

    auto arrange(Rect rect) -> void override
    {
        Widget::arrange(rect);
        m_native.setRect(rect);
    }

    auto set(SliderProps props) -> Slider&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto on(SliderEvents events) -> Slider&
    {
        m_events = std::move(events);
        return *this;
    }

    auto id(WidgetId& id) -> Slider&
    {
        id = m_id;
        return *this;
    }

private:
    NativeSlider m_native;
    SliderProps m_props;
    SliderEvents m_events;

    int m_value;
};


} // namespace

#include "Slider.h"


namespace Blade {


Slider::Slider(int value) : m_value(value)
{
}

auto Slider::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    m_native.create(ctx, m_id, m_props, m_value);

    bindEvent(ctx, WidgetEvent::Change, [this](const EventValue& value)
    {
        // auto value = std::get<int>(value);
        // TODO Slider change callback
    });
}


} // namespace

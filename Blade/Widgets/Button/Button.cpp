#include "Button.h"


namespace Blade {


Button::Button(std::string text) : m_text(std::move(text))
{
}

auto Button::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    m_native.create(ctx, m_id, m_props, m_text);

    bindEvent(ctx, WidgetEvent::Click, [this](const EventValue&)
    {
        // TODO .on(Callbacks) Button
        // if (m_onClick == nullptr) return;
        // m_onClick();
    });
}


} // namespace

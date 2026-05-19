#include "Button.h"


namespace Blade {


Button::Button(std::string text) : m_text(std::move(text))
{
}

auto Button::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    // m_native.create(ctx, m_id, m_props, m_text);

    bindEvent(ctx, WidgetEvent::Click, [this](const EventValue&)
    {
        // std::cout << m_id <<"_btn\n"; // todo dev
        if (m_events.click == nullptr) return;
        m_events.click();
    });
}


} // namespace

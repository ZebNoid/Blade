#include "TextField.h"


namespace Blade {

TextField::TextField(const std::string& text) : m_text(text)
{
}

auto TextField::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    m_native.create(ctx, m_id, m_props, m_text);

    bindEvent(ctx, WidgetEvent::Change, [this](const EventValue& value)
    {
        if (m_callbacks.change == nullptr) return;
        const auto& text = std::get<std::string>(value);
        m_callbacks.change(text);
    });


    bindEvent(ctx, WidgetEvent::Focus, [this](const EventValue& value)
    {
        if (m_callbacks.focus == nullptr) return;
        const auto focus = std::get<bool>(value);
        m_callbacks.focus(focus);
    });
}


} // namespace

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
        // const auto& text = std::get<std::string>(value);
        // if (m_onChange == nullptr) return;
        // m_onChange(text);
        // TODO .on(Callbacks) TextField
    });


    bindEvent(ctx, WidgetEvent::Focus, [this](const EventValue& value)
    {
        // const auto focus = std::get<bool>(value);
        // if (m_onFocus == nullptr) return;
        // m_onFocus(focus);
        // TODO .on(Callbacks) TextField
    });
}


} // namespace

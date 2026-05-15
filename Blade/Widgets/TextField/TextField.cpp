#include "TextField.h"

TextField::TextField()
{
}

auto TextField::Mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = AllocateId(ctx);
    m_native.Create(ctx, m_id);
    BindEvent(ctx, WidgetEvent::Change, [this](const EventValue& value)
    {
        const auto& text = std::get<std::string>(value);
        if (m_onChange == nullptr) return;
        m_onChange(text);
    });


    BindEvent(ctx, WidgetEvent::Focus, [this](const EventValue& value)
    {
        const auto focus = std::get<bool>(value);
        if (m_onFocus == nullptr) return;
        m_onFocus(focus);
    });
}

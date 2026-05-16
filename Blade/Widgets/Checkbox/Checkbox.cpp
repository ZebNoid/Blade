#include "Checkbox.h"


namespace Blade {


Checkbox::Checkbox(std::string text) : m_text(text)
{
}

auto Checkbox::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    m_native.create(ctx, m_id, m_text);

    bindEvent(ctx, WidgetEvent::Change, [this](const EventValue& value)
    {
        // auto isTrue = std::get<bool>(value);
        // TODO Checkbox change callback
    });
}


} // namespace

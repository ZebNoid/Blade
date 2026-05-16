#include "RadioButton.h"


namespace Blade {


RadioButton::RadioButton(std::string text) : m_text(text)
{
}

auto RadioButton::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    m_native.create(ctx, m_id, m_text);

    bindEvent(ctx, WidgetEvent::Change, [this](const EventValue& value)
    {
        auto isTrue = std::get<bool>(value);
        // TODO RadioButton change callback
        std::cout << m_id << " RadioButton " << isTrue <<"\n";
    });
}


} // namespace

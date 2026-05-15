#include "Button.h"

#include "../../Native/NativeButton/NativeButton.h"

Button::Button(std::string text) : m_text(std::move(text))
{
}

auto Button::Mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = AllocateId(ctx);
    m_native.Create(ctx, m_id, m_text.c_str());
    BindEvent(ctx, WidgetEvent::Click, [this](const EventValue&)
    {
        if (m_onClick == nullptr) return;
        m_onClick();
    });
}

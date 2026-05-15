#include "Widget.h"

#include "../../Windows/Window/Window.h"

auto Widget::AllocateId(const WidgetContext& ctx) -> WidgetId
{
    return static_cast<Window*>(ctx.window)->Router().AllocateId();
}

auto Widget::BindEvent(const WidgetContext& ctx, const WidgetEvent event, const EventHandler& fn) const -> void
{
    static_cast<Window*>(ctx.window)->Router().BindEvent(m_id, event, fn);
}

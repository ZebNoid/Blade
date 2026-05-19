#include "Widget.h"

#include "Windows/Window/Window.h"


namespace Blade {


auto Widget::allocateId(const WidgetContext& ctx) -> WidgetId
{
    return static_cast<Window*>(ctx.window)->router().allocateId();
}

auto Widget::bindEvent(const WidgetContext& ctx, const WidgetEvent event, const EventHandler& fn) const -> void
{
    static_cast<Window*>(ctx.window)->router().bindEvent(m_id, event, fn);
}


} // namespace

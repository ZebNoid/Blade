#include "Progress.h"


namespace Blade {


Progress::Progress(int value) : m_value(value)
{
}

auto Progress::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);

    bindEvent(ctx, WidgetEvent::Change, [this](const EventValue& value)
    {
        // auto value = std::get<int>(value);
        // TODO .on(Callbacks) Progress
    });
}


} // namespace

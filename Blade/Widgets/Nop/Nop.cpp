#include "Nop.h"


namespace Blade {

Nop::Nop(std::string text) : m_text(std::move(text))
{
}

auto Nop::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_id = allocateId(ctx);
    m_native.create(ctx, m_id, m_props, m_text);
}


} // namespace

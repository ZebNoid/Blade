#include "Label.h"


namespace Blade {


Label::Label(std::string text) : m_text(std::move(text))
{
}

auto Label::mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_native.create(ctx, m_text);
}


} // namespace

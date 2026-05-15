#include "Label.h"

Label::Label(std::string text) : m_text(std::move(text))
{
}

auto Label::Mount(Materializer& m, WidgetContext& ctx) -> void
{
    m_native.Create(ctx, m_text.c_str());
}

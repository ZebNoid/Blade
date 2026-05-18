#include "NativeNop.h"


namespace Blade {


auto NativeNop::create(const WidgetContext& ctx, WidgetId id, const NopProps& props, const std::string& text) -> void
{
    NativeCustom::create(ctx, id);
    m_props = props;
    m_text = text;
}
} // namespace

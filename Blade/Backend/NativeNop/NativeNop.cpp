#include "NativeNop.h"

#include "Backend/NativeRender/NativeRender.h"


namespace Blade {


auto NativeNop::create(const WidgetContext& ctx, WidgetId id, const NopProps& props, const std::string& text) -> void
{
    NativeCustom::create(ctx, id);
    m_props = props;
    m_text = Utf8ToUtf16(text);
}

auto NativeNop::paint(const HDC hdc, const RECT rect) -> void
{
    // m_render.rectFill(hdc, rect, RGB(40, 40, 40));

    m_render.frame(hdc, rect, RGB(0, 0, 255));
    // m_render.rect(hdc, rect, RGB(0, 0, 255), 2);

    m_render.line(
        hdc,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom,
        RGB(255, 0, 0)
    );

    m_render.line(
        hdc,
        rect.left + rect.right,
        rect.top,
        rect.left,
        rect.top + rect.bottom,
        RGB(0, 255, 0)
    );

    m_render.text(
        hdc,
        rect,
        m_text,
        RGB(128, 128, 128),
        m_systemFont
    );
}


} // namespace

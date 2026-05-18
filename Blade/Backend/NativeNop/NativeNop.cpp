#include "NativeNop.h"

#include "Backend/NativeRender/NativeRender.h"


namespace Blade {


auto NativeNop::create(const WidgetContext& ctx, WidgetId id, const NopProps& props, const std::string& text) -> void
{
    NativeCustom::create(ctx, id);
    m_props = props;
    m_text = Utf8ToUtf16(text);
}

auto NativeNop::paint(HDC hdc, RECT rect) -> void
{
    std::cout << "NativeNop!!\n";
    m_render.fillRect(
        hdc,
        rect,
        RGB(40, 40, 40)
    );

    m_render.drawRect(
        hdc,
        rect,
        RGB(255, 0, 0),
        2
    );

    m_render.drawLine(
        hdc,
        rect.left,
        rect.top,
        // rect.left + rect.right,
        // rect.top + rect.bottom,
        rect.right,
        rect.bottom,
        RGB(255, 0, 0)
    );

    m_render.drawLine(
        hdc,
        rect.left + rect.right,
        rect.top,
        rect.left,
        rect.top + rect.bottom,
        (255, 0, 0)
    );

    m_render.drawText(
        hdc,
        rect,
        m_text,
        RGB(255, 255, 255)
    );
}
} // namespace

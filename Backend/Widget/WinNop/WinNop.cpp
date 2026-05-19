#include "WinNop.h"



namespace Blade::Backend {


WinNop::WinNop(Widget& widget)
{
    // std::cout << "WinNop::WinNop\n"; // TODO dev
}

WinNop::WinNop(const std::wstring& text) : m_text(text)
{
    // std::cout << "WinNop::WinNop" << Utf16ToUtf8(m_text) << "\n"; // TODO dev
}

auto WinNop::create(WidgetId id, const NopProps& props, const std::string& text) -> void
{
    WinCustom::create(id);
    m_props = props;
    m_text = Utf8ToUtf16(text);

    std::cout << "WinNop::create\n"; // TODO dev
}

auto WinNop::create(ApiWidget& parent) -> void
{
}

auto WinNop::paint(const HDC hdc, const RECT rect) -> void
{
    std::cout << "WinNop::paint\n";
    m_render.rectFill(hdc, rect, RGB(40, 40, 40));

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

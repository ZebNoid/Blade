#include "WinNop.h"

#include "Core/Encoding.h"


namespace Blade::Backend {


WinNop::WinNop(Widget& widget)
{
    std::cout << "-> WinNop::WinNop Widget&\n"; // TODO dev
}

WinNop::WinNop(const std::wstring& text) : m_text(text)
{

    std::cout << "-> WinNop::WinNop TEXT: " << Utf16ToUtf8(m_text) << "\n"; // TODO dev
}

auto WinNop::create(ApiWidget& parent) -> void
{
    m_parent = &parent;
    if (!parentHandle())
    {
        std::cerr << " -> WinNop::create no parent1\n"; // TODO dev
        return;
    }
    create(0, {}, L"test Nop"); //TODO
}

auto WinNop::create(WidgetId id, const NopProps& props, const std::wstring& text) -> void
{
    WinCustom::create(id);
    m_props = props;
    m_text = text;

    std::cout << " -> WinNop::create  props2\n"; // TODO dev
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

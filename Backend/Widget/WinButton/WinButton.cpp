#include "WinButton.h"

#include "Registry/ResourceRegistry/ResourceRegistry.h"
#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


WinButton::WinButton(Widget& widget)
{
    std::cout << " -> WinButton::WinButton  Widget&\n"; // TODO dev
}

auto WinButton::create(ApiWidget& parent) -> void
{
    // auto* winParent = dynamic_cast<WinWindow*>(&parent);
    // m_hwndParent = winParent->handle();

    if (!parentHandle())
    {
        return;
    }

    std::cout << " -> WinButton::create ApiWidget&  hwnd: " << parentHandle() << "\n"; // TODO dev

    create(0, {}, L"");
}

auto WinButton::create(
    const WidgetId id,
    const ButtonProps& props,
    const std::wstring& text
) -> void
{
    m_id = id;
    m_props = props;
    m_text = text;

    // TODO native size?
    // size are ignoring and recalculated in Widget->Measure
    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));
}

DWORD WinButton::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_CLIPSIBLINGS;

    if (m_props.defaultButton)
    {
        style |= BS_DEFPUSHBUTTON;
    }

    // TODO
    // BS_NOTIFY to send BN_DBLCLK, BN_SETFOCUS, BN_KILLFOCUS

    return style;
}

auto WinButton::createNative(const Rect rect) -> HWND
{
    m_hwnd = CreateWindowEx(
        0,
        TEXT("BUTTON"),
        m_text.c_str(),
        style(),
        rect.x, rect.y,
        rect.width, rect.height,
        parentHandle(),
        (HMENU)m_id, // Button ID
        GetModuleHandle(nullptr), // TODO m_ctx.app->hInstance,
        nullptr);

    if (!m_hwnd)
    {
        std::cerr << "[Error] WinButton::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}


} // namespace

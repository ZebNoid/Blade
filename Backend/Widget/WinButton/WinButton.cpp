#include "WinButton.h"

#include "Registry/ResourceRegistry/ResourceRegistry.h"
#include "Context/WidgetContext.h"


namespace Blade::Backend {


auto WinButton::create(
    const WidgetContext& ctx,
    const WidgetId id,
    const ButtonProps& props,
    const std::string& text
) -> void
{
    m_ctx = ctx;
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
    ApiWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        TEXT("BUTTON"),
        toNativeString(m_text).c_str(),
        style(),
        rect.x, rect.y,
        rect.width, rect.height,
        m_ctx.hwnd,
        (HMENU)m_id, // Button ID
        m_ctx.app->hInstance,
        nullptr);

    if (!m_hwnd)
    {
        std::cerr << "[Error] WinButton::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}


} // namespace

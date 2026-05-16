#include "NativeTextField.h"

#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade {


auto NativeTextField::create(const WidgetContext& ctx, const WidgetId id) -> void
{
    m_ctx = ctx;
    m_id = id;

    // TODO native size?
    // size are ignoring and recalculated in
    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::get_font("system"));
}

auto NativeTextField::createNative(const Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        L"EDIT",
        nullptr,
        // WS_BORDER
        // ES_AUTOHSCROLL || WS_EX_CLIENTEDGE || WS_EX_TRANSPARENT
        // ES_LEFT ES_CENTER ES_RIGHT
        WS_BORDER | WS_CHILD | WS_EX_TRANSPARENT | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL |
        ES_AUTOHSCROLL,
        // WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT | ES_LEFT | ES_MULTILINE, // Styles
        rect.x, rect.y,
        rect.width, rect.height,
        m_ctx.hwnd,
        (HMENU)m_id, // ID
        m_ctx.app->hInstance,
        nullptr);

    if (!m_hwnd)
    {
        std::cerr << "[Error] NativeTextField::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}


auto NativeTextField::setRect(const Rect rect) -> void
{
    SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
    VerticalAlignCenter(m_hwnd);
}


} // namespace

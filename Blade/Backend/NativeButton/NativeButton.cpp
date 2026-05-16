#include "NativeButton.h"

#include "Backend/NativeWidget/NativeWidget.h"
#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"
#include "Context/WidgetContext.h"


namespace Blade {


auto NativeButton::create(const WidgetContext& ctx, const WidgetId id, const std::string& text) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_text = text;

    // TODO native size?
    // size are ignoring and recalculated in Widget->Measure
    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::get_font("system"));
}

auto NativeButton::createNative(const Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        L"BUTTON",
        toNativeString(m_text).c_str(),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        rect.x, rect.y,
        rect.width, rect.height,
        m_ctx.hwnd,
        (HMENU)m_id, // Button ID
        m_ctx.app->hInstance,
        nullptr);

    if (!m_hwnd)
    {
        std::cerr << "[Error] NativeButton::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto NativeButton::setRect(const Rect rect) -> void
{
    MoveWindow(m_hwnd, rect.x, rect.y, rect.width, rect.height, TRUE);
}


} // namespace

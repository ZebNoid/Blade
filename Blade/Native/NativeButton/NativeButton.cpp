#include "NativeButton.h"

#include "../../Context/WidgetContext.h"
#include "../NativeWidget/NativeWidget.h"
#include "../Registry/ResourceRegistry/ResourceRegistry.h"


auto NativeButton::Create(const WidgetContext& ctx, const WidgetId id, const std::string& text) -> void
{
    m_text = text;
    m_id = id;
    m_ctx = ctx;

    // TODO native size?
    // size are ignoring and recalculated in Widget->Measure
    CreateNative(Rect{0, 0, 140, 32});
    ApplyFont(ResourceRegistry::GetFont("system"));
}

auto NativeButton::CreateNative(const Rect rect) -> HWND
{
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
        std::cerr << "[Error] " << NAME_OF(NativeButton::CreateNative) << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto NativeButton::SetRect(const Rect rect) -> void
{
    MoveWindow(m_hwnd, rect.x, rect.y, rect.width, rect.height, TRUE);
}

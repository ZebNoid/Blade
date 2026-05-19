#include "WinProgress.h"

#include <commctrl.h>
// #include <uxtheme.h>

#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {


auto WinProgress::create(
    const WidgetContext& ctx,
    const WidgetId id,
    const ProgressProps& props,
    const int value
) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_props = props;
    m_value = value;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));

    // std::cout << GetSystemMetrics(SM_CYVSCROLL);  // Get system value heught?

    // all messages https://learn.microsoft.com/en-us/windows/win32/controls/progress-bar-control-reference?source=recommendations
    // SendMessage(m_hwnd, PBM_SETRANGE32, (WPARAM)0, (LPARAM)1000); // Set Range 0 - 1000
    // SendMessage(m_hwnd, PBM_SETPOS, (WPARAM)45, 0); // set value 45

    // SendMessage(m_hwnd, PBM_SETSTATE, PBST_PAUSED, 0); // pause Yellow
    // SendMessage(m_hwnd, PBM_SETSTATE, PBST_ERROR, 0); // stop Red
    // SendMessage(m_hwnd, PBM_SETSTATE, PBST_NORMAL, 0); // progress Green

    if (m_props.marquee)
    {
        // https://learn.microsoft.com/en-us/windows/win32/controls/progress-bar-control#marquee-style
        SendMessage(m_hwnd, PBM_SETMARQUEE, (WPARAM)TRUE, 0); // pulsing? use with style PBS_MARQUEE
    }

    // SetWindowTheme(m_hwnd, L"", L""); // disable theme for selected hwnd
    // SendMessage(m_hwnd, PBM_SETBARCOLOR , 0, (LPARAM)RGB(255, 0, 0));

    SendMessage(m_hwnd, PBM_SETPOS, (WPARAM)value, 0);
    // SendMessage(m_hwnd, PBM_SETSTATE, PBST_PAUSED, 0); // pause Yellow
}

DWORD WinProgress::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
    if (m_props.vertical)
    {
        style |= PBS_VERTICAL;
    }

    // old
    // style |= PBS_SMOOTH;
    // style |= PBS_SMOOTHREVERSE;

    if (m_props.marquee)
    {
        // pulsing (not theme)
        style |= PBS_MARQUEE;
    }
    return style;
}

auto WinProgress::createNative(Rect rect) -> HWND
{
    WinWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        PROGRESS_CLASS, // Predefined class
        nullptr,
        style(),
        rect.x,
        rect.y,
        rect.width,
        rect.height,
        m_ctx.hwnd,
        (HMENU)m_id, // Checkbox ID
        m_ctx.app->hInstance,
        this
    );

    if (!m_hwnd)
    {
        std::cerr << "[Error] CheckboxNative::CreateNative " << GetLastError() << std::endl;
    }

    return m_hwnd;
}


} // namespace

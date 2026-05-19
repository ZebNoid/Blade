#include "WinWidget.h"


namespace Blade::Backend {


WinWidget::~WinWidget()
{
    // TODO check for windows and children
    if (m_hwnd && IsWindow(m_hwnd))
    {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

auto WinWidget::handle() const -> HWND
{
    return m_hwnd;
}

auto WinWidget::style() const -> DWORD
{
    return WS_CHILD | WS_VISIBLE;
}

auto WinWidget::exStyle() const -> DWORD
{
    return 0;
}

auto WinWidget::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

auto WinWidget::applyFont(HFONT font) const -> void
{
    // auto font = GetSystemUIFont();
    SendMessageW(m_hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}

auto WinWidget::setRect(const Rect& rect) -> void
{
    SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NONE);
    // SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
}

auto WinWidget::show() -> void
{
    ShowWindow(m_hwnd, SW_SHOW);
}

auto WinWidget::hide() -> void
{
    ShowWindow(m_hwnd, SW_HIDE);
}

auto CALLBACK WinWidget::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    WinWidget* widget = nullptr;

    if (msg == WM_NCCREATE)
    {
        auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);

        widget = static_cast<WinWidget*>(cs->lpCreateParams);

        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(widget));

        widget->m_hwnd = hwnd;
    }
    else
    {
        widget = reinterpret_cast<WinWidget*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (widget)
    {
        return widget->handleMessage(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// TODO z order
// auto updateZOrder() -> void;
// auto NativeWidget::updateZOrder() -> void
// {
// HWND previous = nullptr;
//
// for (auto it = m_children.rbegin();         it != m_children.rend();         ++it)
// {
//     auto hwnd = (*it)->nativeHandle();
//
//     SetWindowPos(
//         hwnd,
//         previous,
//         0,
//         0,
//         0,
//         0,
//         SWP_NOMOVE |
//         SWP_NOSIZE |
//         SWP_NOACTIVATE
//     );
//
//     previous = hwnd;
// }
// }

} // namespace

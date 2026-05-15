#include "NativeWidget.h"


NativeWidget::~NativeWidget()
{
    // TODO check for windows and children
    if (m_hwnd && IsWindow(m_hwnd))
    {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

auto NativeWidget::handle() const -> HWND
{
    return m_hwnd;
}

auto NativeWidget::style() const -> DWORD
{
    return WS_CHILD | WS_VISIBLE;
}

auto NativeWidget::exStyle() const -> DWORD
{
    return 0;
}

auto NativeWidget::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

auto NativeWidget::applyFont(HFONT font) const -> void
{
    // auto font = GetSystemUIFont();
    SendMessageW(m_hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}

auto CALLBACK NativeWidget::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    NativeWidget* widget = nullptr;

    if (msg == WM_NCCREATE)
    {
        auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);

        widget = static_cast<NativeWidget*>(cs->lpCreateParams);

        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(widget));

        widget->m_hwnd = hwnd;
    }
    else
    {
        widget = reinterpret_cast<NativeWidget*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (widget)
    {
        return widget->handleMessage(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

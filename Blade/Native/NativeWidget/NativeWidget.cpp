#include "NativeWidget.h"


NativeWidget::~NativeWidget()
{
    if (m_hwnd && IsWindow(m_hwnd))
    {
        DestroyWindow(m_hwnd);
    }
}

auto NativeWidget::Handle() const -> HWND
{
    return m_hwnd;
}

auto NativeWidget::Style() const -> DWORD
{
    return WS_CHILD | WS_VISIBLE;
}

auto NativeWidget::ExStyle() const -> DWORD
{
    return 0;
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
        return widget->HandleMessage(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

auto NativeWidget::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

auto NativeWidget::ApplyFont(HFONT font) const -> void
{
    // auto font = GetSystemUIFont();
    SendMessageW(m_hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}
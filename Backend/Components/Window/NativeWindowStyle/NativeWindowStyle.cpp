#include "NativeWindowStyle.h"

namespace Blade::Backend {

namespace {

auto Has(Api::CaptionButton value, Api::CaptionButton flag) -> bool
{
    return (static_cast<int>(value) & static_cast<int>(flag)) != 0;
}

auto SetStyleFlag(DWORD& style, DWORD flag, bool enabled) -> void
{
    if (enabled)
    {
        style |= flag;
    }
    else
    {
        style &= ~flag;
    }
}

auto SetCaptionButtons(HWND hwnd, Api::CaptionButton buttons) -> void
{
    auto* systemMenu = GetSystemMenu(hwnd, FALSE);
    if (!systemMenu) return;

    EnableMenuItem(systemMenu, SC_CLOSE, MF_BYCOMMAND | (Has(buttons, Api::CaptionButton::Close) ? MF_ENABLED : MF_GRAYED));
}

auto SetFrameChanged(HWND hwnd) -> void
{
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

} // namespace

auto NativeWindowStyle::SetCaption(HWND hwnd, const Api::CaptionProps& caption) -> void
{
    auto style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));

    SetStyleFlag(style, WS_CAPTION, caption.visible);
    SetStyleFlag(style, WS_MINIMIZEBOX, Has(caption.buttons, Api::CaptionButton::Min));
    SetStyleFlag(style, WS_MAXIMIZEBOX, Has(caption.buttons, Api::CaptionButton::Max));

    SetWindowLongPtr(hwnd, GWL_STYLE, static_cast<LONG_PTR>(style));
    SetCaptionButtons(hwnd, caption.buttons);
    SetFrameChanged(hwnd);
}

auto NativeWindowStyle::SetResizable(HWND hwnd, bool resizable) -> void
{
    auto style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));
    SetStyleFlag(style, WS_THICKFRAME, resizable);
    SetWindowLongPtr(hwnd, GWL_STYLE, static_cast<LONG_PTR>(style));
    SetFrameChanged(hwnd);
}

auto NativeWindowStyle::SetTaskbar(HWND hwnd, bool taskbar) -> void
{
    auto exStyle = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_EXSTYLE));
    SetStyleFlag(exStyle, WS_EX_APPWINDOW, taskbar);
    SetStyleFlag(exStyle, WS_EX_TOOLWINDOW, !taskbar);
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, static_cast<LONG_PTR>(exStyle));
    SetFrameChanged(hwnd);
}

} // namespace Blade::Backend

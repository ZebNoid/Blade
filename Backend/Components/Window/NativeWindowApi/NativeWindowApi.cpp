#include "NativeWindowApi.h"

#include "Components/Window/NativeWindowPlacement/NativeWindowPlacement.h"
#include "WinApi/Resource/ImageLoader/ImageLoader.h"

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

    if (!systemMenu)
    {
        return;
    }
    // TODO later extract to Context menu helper class
    EnableMenuItem(systemMenu, SC_CLOSE, MF_BYCOMMAND | (Has(buttons, Api::CaptionButton::Close) ? MF_ENABLED : MF_GRAYED));
}

auto SetFrameChanged(HWND hwnd) -> void
{
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

} // namespace

auto NativeWindowApi::SetCaption(HWND hwnd, const Api::CaptionProps& caption) -> void
{
    auto style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));

    SetStyleFlag(style, WS_CAPTION, caption.visible);
    SetStyleFlag(style, WS_MINIMIZEBOX, Has(caption.buttons, Api::CaptionButton::Min));
    SetStyleFlag(style, WS_MAXIMIZEBOX, Has(caption.buttons, Api::CaptionButton::Max));

    SetWindowLongPtr(hwnd, GWL_STYLE, static_cast<LONG_PTR>(style));
    SetCaptionButtons(hwnd, caption.buttons);
    SetFrameChanged(hwnd);
}

auto NativeWindowApi::SetIcon(HWND hwnd, const Api::Text& icon) -> HICON
{
    auto bigIcon = ImageLoader::LoadIcon(icon, 32, 32);
    auto smallIcon = ImageLoader::IsIcon(icon) ? ImageLoader::LoadIcon(icon, 16, 16) : (bigIcon ? CopyIcon(bigIcon) : nullptr);

    if (bigIcon) SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(bigIcon));
    if (smallIcon) SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(smallIcon));

    return bigIcon;
}

auto NativeWindowApi::SetPlacement(HWND hwnd, const Api::WindowPlacementProps& placement) -> void
{
    const auto rect = NativeWindowPlacement::ToRect(hwnd, placement);
    SetWindowPos(hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER | SWP_NOACTIVATE);
}

auto NativeWindowApi::SetNormalPlacement(HWND hwnd, const Api::WindowPlacementProps& placement, const Api::Size& windowSize) -> void
{
    SetNormalRect(hwnd, NativeWindowPlacement::ToRect(placement, windowSize));
}

auto NativeWindowApi::SetNormalRect(HWND hwnd, const Api::Rect& rect) -> void
{
    WINDOWPLACEMENT placement{sizeof(WINDOWPLACEMENT)};

    if (!GetWindowPlacement(hwnd, &placement))
    {
        return;
    }

    placement.rcNormalPosition = NativeWindowPlacement::ToWinRect(rect);
    SetWindowPlacement(hwnd, &placement);
}

auto NativeWindowApi::SetResizable(HWND hwnd, bool resizable) -> void
{
    auto style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));
    SetStyleFlag(style, WS_THICKFRAME, resizable);
    SetWindowLongPtr(hwnd, GWL_STYLE, static_cast<LONG_PTR>(style));
    SetFrameChanged(hwnd);
}

auto NativeWindowApi::SetTaskbar(HWND hwnd, bool taskbar) -> void
{
    auto exStyle = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_EXSTYLE));
    SetStyleFlag(exStyle, WS_EX_APPWINDOW, taskbar);
    SetStyleFlag(exStyle, WS_EX_TOOLWINDOW, !taskbar);
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, static_cast<LONG_PTR>(exStyle));
    SetFrameChanged(hwnd);
}

auto NativeWindowApi::SetTopMost(HWND hwnd, bool topMost) -> void
{
    SetWindowPos(hwnd, topMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

auto NativeWindowApi::SetState(HWND hwnd, Api::WindowState state) -> void
{
    const bool visible = IsWindowVisible(hwnd);

    switch (state)
    {
    case Api::WindowState::Normal:
        ShowWindow(hwnd, visible ? SW_RESTORE : SW_SHOWNORMAL);
        break;

    case Api::WindowState::Minimized:
        ShowWindow(hwnd, visible ? SW_MINIMIZE : SW_SHOWMINIMIZED);
        break;

    case Api::WindowState::Maximized:
        ShowWindow(hwnd, visible ? SW_MAXIMIZE : SW_SHOWMAXIMIZED);
        break;
    }
}

} // namespace Blade::Backend

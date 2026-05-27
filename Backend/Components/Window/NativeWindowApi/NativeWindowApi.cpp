#include "NativeWindowApi.h"

#include "Components/Window/NativeWindowPlacement/NativeWindowPlacement.h"
#include "WinApi/Resource/ImageLoader/ImageLoader.h"

namespace Blade::Backend {

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

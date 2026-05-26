#include "NativeWindowApi.h"

#include "WinApi/DisplayApi/DisplayApi.h"

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

auto GetWindowSize(HWND hwnd) -> Api::Size
{
    RECT rect{};
    GetWindowRect(hwnd, &rect);
    return {rect.right - rect.left, rect.bottom - rect.top};
}

auto ToRect(HWND hwnd, const Api::WindowPlacementProps& placement) -> Api::Rect
{
    const auto screen = DisplayApi::WorkArea(placement.monitor);
    auto size = GetWindowSize(hwnd);

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        break;

    case Api::WindowAnchor::TopFill:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::BottomFill:
    case Api::WindowAnchor::Fill:
        size.width = screen.width;
        break;

    default:
        break;
    }

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        break;

    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::CenterVerticalFill:
    case Api::WindowAnchor::RightFill:
    case Api::WindowAnchor::Fill:
        size.height = screen.height;
        break;

    default:
        break;
    }

    Api::Point position{};

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        position.x = placement.offset.x;
        break;

    case Api::WindowAnchor::TopLeft:
    case Api::WindowAnchor::TopFill:
    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::Fill:
        position.x = screen.x;
        break;

    case Api::WindowAnchor::TopCenter:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::CenterVerticalFill:
        position.x = screen.x + (screen.width - size.width) / 2;
        break;

    case Api::WindowAnchor::TopRight:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::RightFill:
        position.x = screen.x + screen.width - size.width;
        break;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomFill:
        position.x = screen.x;
        break;
    }

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        position.y = placement.offset.y;
        break;

    case Api::WindowAnchor::TopLeft:
    case Api::WindowAnchor::TopCenter:
    case Api::WindowAnchor::TopRight:
    case Api::WindowAnchor::TopFill:
        position.y = screen.y;
        break;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::CenterHorizontalFill:
        position.y = screen.y + (screen.height - size.height) / 2;
        break;

    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::BottomFill:
        position.y = screen.y + screen.height - size.height;
        break;

    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::CenterVerticalFill:
    case Api::WindowAnchor::RightFill:
    case Api::WindowAnchor::Fill:
        position.y = screen.y;
        break;
    }

    if (placement.anchor != Api::WindowAnchor::Manual)
    {
        position.x += placement.offset.x;
        position.y += placement.offset.y;
    }

    return {position, size};
}

auto ToRect(const Api::WindowPlacementProps& placement, Api::Size size) -> Api::Rect
{
    const auto screen = DisplayApi::WorkArea(placement.monitor);

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        break;

    case Api::WindowAnchor::TopFill:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::BottomFill:
    case Api::WindowAnchor::Fill:
        size.width = screen.width;
        break;

    default:
        break;
    }

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        break;

    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::CenterVerticalFill:
    case Api::WindowAnchor::RightFill:
    case Api::WindowAnchor::Fill:
        size.height = screen.height;
        break;

    default:
        break;
    }

    Api::Point position{};

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        position.x = placement.offset.x;
        break;

    case Api::WindowAnchor::TopLeft:
    case Api::WindowAnchor::TopFill:
    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::Fill:
        position.x = screen.x;
        break;

    case Api::WindowAnchor::TopCenter:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::CenterVerticalFill:
        position.x = screen.x + (screen.width - size.width) / 2;
        break;

    case Api::WindowAnchor::TopRight:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::RightFill:
        position.x = screen.x + screen.width - size.width;
        break;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomFill:
        position.x = screen.x;
        break;
    }

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        position.y = placement.offset.y;
        break;

    case Api::WindowAnchor::TopLeft:
    case Api::WindowAnchor::TopCenter:
    case Api::WindowAnchor::TopRight:
    case Api::WindowAnchor::TopFill:
        position.y = screen.y;
        break;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::CenterHorizontalFill:
        position.y = screen.y + (screen.height - size.height) / 2;
        break;

    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::BottomFill:
        position.y = screen.y + screen.height - size.height;
        break;

    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::CenterVerticalFill:
    case Api::WindowAnchor::RightFill:
    case Api::WindowAnchor::Fill:
        position.y = screen.y;
        break;
    }

    if (placement.anchor != Api::WindowAnchor::Manual)
    {
        position.x += placement.offset.x;
        position.y += placement.offset.y;
    }

    return {position, size};
}

auto ToWinRect(const Api::Rect& rect) -> RECT
{
    return {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
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

auto NativeWindowApi::SetPlacement(HWND hwnd, const Api::WindowPlacementProps& placement) -> void
{
    const auto rect = ToRect(hwnd, placement);
    SetWindowPos(hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER | SWP_NOACTIVATE);
}

auto NativeWindowApi::SetNormalPlacement(HWND hwnd, const Api::WindowPlacementProps& placement, const Api::Size& windowSize) -> void
{
    SetNormalRect(hwnd, ToRect(placement, windowSize));
}

auto NativeWindowApi::SetNormalRect(HWND hwnd, const Api::Rect& rect) -> void
{
    WINDOWPLACEMENT placement{sizeof(WINDOWPLACEMENT)};

    if (!GetWindowPlacement(hwnd, &placement))
    {
        return;
    }

    placement.rcNormalPosition = ToWinRect(rect);
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

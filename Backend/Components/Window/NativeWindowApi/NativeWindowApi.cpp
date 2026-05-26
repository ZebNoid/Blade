#include "NativeWindowApi.h"

namespace Blade::Backend {

namespace {

struct MonitorSearch
{
    int target = 0;
    int index = 0;
    RECT rect{};
    bool found = false;
};

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

auto SearchMonitor(HMONITOR monitor, HDC, LPRECT, LPARAM data) -> BOOL
{
    auto* search = reinterpret_cast<MonitorSearch*>(data);

    if (search->index == search->target)
    {
        MONITORINFO info{sizeof(MONITORINFO)};
        if (GetMonitorInfo(monitor, &info))
        {
            search->rect = info.rcWork;
            search->found = true;
        }

        return FALSE;
    }

    ++search->index;
    return TRUE;
}

auto GetMonitorRect(int monitor) -> RECT
{
    MonitorSearch search{.target = monitor};
    EnumDisplayMonitors(nullptr, nullptr, SearchMonitor, reinterpret_cast<LPARAM>(&search));

    if (search.found)
    {
        return search.rect;
    }

    MONITORINFO info{sizeof(MONITORINFO)};
    GetMonitorInfo(MonitorFromWindow(nullptr, MONITOR_DEFAULTTOPRIMARY), &info);
    return info.rcWork;
}

auto GetWindowSize(HWND hwnd) -> Api::Size
{
    RECT rect{};
    GetWindowRect(hwnd, &rect);
    return {rect.right - rect.left, rect.bottom - rect.top};
}

auto ToRect(HWND hwnd, const Api::WindowPlacementProps& placement) -> Api::Rect
{
    const auto screen = GetMonitorRect(placement.monitor);
    const auto screenWidth = screen.right - screen.left;
    const auto screenHeight = screen.bottom - screen.top;
    auto size = GetWindowSize(hwnd);

    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        break;

    case Api::WindowAnchor::TopFill:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::BottomFill:
    case Api::WindowAnchor::Fill:
        size.width = screenWidth;
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
        size.height = screenHeight;
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
        position.x = screen.left;
        break;

    case Api::WindowAnchor::TopCenter:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::CenterVerticalFill:
        position.x = screen.left + (screenWidth - size.width) / 2;
        break;

    case Api::WindowAnchor::TopRight:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::RightFill:
        position.x = screen.right - size.width;
        break;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomFill:
        position.x = screen.left;
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
        position.y = screen.top;
        break;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::CenterHorizontalFill:
        position.y = screen.top + (screenHeight - size.height) / 2;
        break;

    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::BottomFill:
        position.y = screen.bottom - size.height;
        break;

    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::CenterVerticalFill:
    case Api::WindowAnchor::RightFill:
    case Api::WindowAnchor::Fill:
        position.y = screen.top;
        break;
    }

    if (placement.anchor != Api::WindowAnchor::Manual)
    {
        position.x += placement.offset.x;
        position.y += placement.offset.y;
    }

    return {position, size};
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
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

auto NativeWindowApi::SetPlacement(HWND hwnd, const Api::WindowPlacementProps& placement) -> void
{
    const auto rect = ToRect(hwnd, placement);
    SetWindowPos(hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER | SWP_NOACTIVATE);
}

} // namespace Blade::Backend

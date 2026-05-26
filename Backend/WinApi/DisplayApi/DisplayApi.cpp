#include "DisplayApi.h"


namespace Blade::Backend {

namespace {

struct MonitorSearch
{
    int target = 0;
    int index = 0;
    RECT rect{};
    bool found = false;
};

auto ToRect(const RECT& rect) -> Api::Rect
{
    return {rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top};
}

auto CountMonitor(HMONITOR, HDC, LPRECT, LPARAM data) -> BOOL
{
    ++(*reinterpret_cast<int*>(data));
    return TRUE;
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

auto PrimaryWorkArea() -> Api::Rect
{
    MONITORINFO info{sizeof(MONITORINFO)};
    GetMonitorInfo(MonitorFromWindow(nullptr, MONITOR_DEFAULTTOPRIMARY), &info);
    return ToRect(info.rcWork);
}

} // namespace

auto DisplayApi::Count() -> int
{
    int count = 0;
    EnumDisplayMonitors(nullptr, nullptr, CountMonitor, reinterpret_cast<LPARAM>(&count));
    return count;
}

auto DisplayApi::WorkArea(int monitor) -> Api::Rect
{
    MonitorSearch search{.target = monitor};
    EnumDisplayMonitors(nullptr, nullptr, SearchMonitor, reinterpret_cast<LPARAM>(&search));
    return search.found ? ToRect(search.rect) : PrimaryWorkArea();
}

auto DisplayApi::DesktopRect() -> Api::Rect
{
    return {
        GetSystemMetrics(SM_XVIRTUALSCREEN),
        GetSystemMetrics(SM_YVIRTUALSCREEN),
        GetSystemMetrics(SM_CXVIRTUALSCREEN),
        GetSystemMetrics(SM_CYVIRTUALSCREEN)
    };
}

} // namespace Blade::Backend

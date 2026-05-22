#include "NativeApi.h"


namespace Blade::Backend {


auto NativeApi::SetTitle(
    HWND hwnd,
    const Api::Text& text
) -> void
{
    SetWindowTextW(hwnd, text.c_str());
}

auto NativeApi::GetTitle(HWND hwnd) -> Api::Text
{
    const int length = GetWindowTextLength(hwnd);
    if (length == 0) return L"";

    Api::Text title;
    title.resize(length);

    GetWindowTextW(hwnd, &title[0], length + 1);

    return title;
}


auto NativeApi::SetSize(
    HWND hwnd,
    const Api::Size& size
) -> void
{
    SetWindowPos(hwnd, nullptr, 0, 0, size.width, size.height, SWP_NOMOVE | SWP_NOZORDER);
}

auto NativeApi::GetSize(HWND hwnd) -> Api::Size
{
    RECT rect;
    if (GetWindowRect(hwnd, &rect))
    {
        return {
            .width = rect.right - rect.left,
            .height = rect.bottom - rect.top,
        };
    }
    return {};
}

auto NativeApi::SetPosition(HWND hwnd, const Api::Point& position) -> void
{
    SetWindowPos(hwnd, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

auto NativeApi::GetPosition(HWND hwnd) -> Api::Point
{
    RECT rect;
    if (GetWindowRect(hwnd, &rect))
    {
        return {
            .x = rect.left,
            .y = rect.top,
        };
    }
    return {};
}

auto NativeApi::Show(HWND hwnd, int cmdShow) -> void
{
    // SW_HIDE             0
    // SW_SHOWNORMAL       1
    // SW_NORMAL           1
    // SW_SHOWMINIMIZED    2
    // SW_SHOWMAXIMIZED    3
    // SW_MAXIMIZE         3
    // SW_SHOWNOACTIVATE   4
    // SW_SHOW             5
    // SW_MINIMIZE         6
    // SW_SHOWMINNOACTIVE  7
    // SW_SHOWNA           8
    // SW_RESTORE          9
    // SW_SHOWDEFAULT      10
    // SW_FORCEMINIMIZE    11
    // SW_MAX              11
    ShowWindow(hwnd, cmdShow);
}

auto NativeApi::Update(HWND hwnd) -> void
{
    UpdateWindow(hwnd);
}

auto NativeApi::Destroy(HWND hwnd) -> void
{
    DestroyWindow(hwnd);
}

auto NativeApi::ScreenSize() -> Api::Size
{
    return {
        .width = GetSystemMetrics(SM_CXSCREEN),
        .height = GetSystemMetrics(SM_CYSCREEN),
    };
}


} // namespace

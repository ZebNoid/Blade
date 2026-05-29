#include "HwndApi.h"


namespace Blade::Backend {

namespace {

auto GetWindowStyle(HWND hwnd) -> DWORD
{
    return static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));
}

auto GetWindowExStyle(HWND hwnd) -> DWORD
{
    return static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_EXSTYLE));
}

auto ToOuterSize(HWND hwnd, const Api::Size& clientSize) -> Api::Size
{
    RECT rect{0, 0, clientSize.width, clientSize.height};
    AdjustWindowRectEx(&rect, GetWindowStyle(hwnd), FALSE, GetWindowExStyle(hwnd));
    return {rect.right - rect.left, rect.bottom - rect.top};
}

} // namespace


auto HwndApi::SetParent(HWND hwnd, HWND hwndParent) -> HWND
{
    return ::SetParent(hwnd, hwndParent);
}

auto HwndApi::GetParent(HWND hwnd) -> HWND
{
    return ::GetParent(hwnd);
}

auto HwndApi::SetTitle(HWND hwnd, const Api::Text& text) -> void
{
    SetWindowTextW(hwnd, text.c_str());
}

auto HwndApi::GetTitle(HWND hwnd) -> Api::Text
{
    const int length = GetWindowTextLength(hwnd);
    if (length == 0) return L"";

    Api::Text title;
    title.resize(length);

    GetWindowTextW(hwnd, &title[0], length + 1);

    return title;
}

auto HwndApi::SetSize(HWND hwnd, const Api::Size& size) -> void
{
    SetWindowPos(hwnd, nullptr, 0, 0, size.width, size.height, SWP_NOMOVE | SWP_NOZORDER);
}

auto HwndApi::SetClientSize(HWND hwnd, const Api::Size& size) -> void
{
    SetSize(hwnd, ToOuterSize(hwnd, size));
}

auto HwndApi::ClientToWindowSize(HWND hwnd, const Api::Size& clientSize) -> Api::Size
{
    return ToOuterSize(hwnd, clientSize);
}

auto HwndApi::SetRect(HWND hwnd, const Api::Rect& rect) -> void
{
    SetWindowPos(hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER | SWP_NOACTIVATE);
}

auto HwndApi::SetClientRect(HWND hwnd, const Api::Rect& rect) -> void
{
    SetRect(hwnd, {rect.position(), ToOuterSize(hwnd, rect.size())});
}

auto HwndApi::GetSize(HWND hwnd) -> Api::Size
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

auto HwndApi::SetPosition(HWND hwnd, const Api::Point& position) -> void
{
    SetWindowPos(hwnd, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

auto HwndApi::BringToFront(HWND hwnd) -> void
{
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

auto HwndApi::GetPosition(HWND hwnd) -> Api::Point
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

auto HwndApi::SetFont(HWND hwnd, HFONT font) -> void
{
    SendMessageW(hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}

auto HwndApi::GetFont(HWND hwnd) -> HFONT
{
    return (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);
}

auto HwndApi::Show(HWND hwnd, int cmdShow) -> void
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

auto HwndApi::SetVisible(HWND hwnd, bool visible) -> void
{
    Show(hwnd, visible ? SW_SHOW : SW_HIDE);

    if (visible)
    {
        Update(hwnd);
    }
}

auto HwndApi::Update(HWND hwnd) -> void
{
    UpdateWindow(hwnd);
}

auto HwndApi::Close(HWND hwnd) -> void
{
    SendMessageW(hwnd, WM_CLOSE, 0, 0);
}

auto HwndApi::Destroy(HWND hwnd) -> void
{
    DestroyWindow(hwnd);
}

auto HwndApi::GetSizeFromLParam(LPARAM lParam) -> Api::Size
{
    return {
        LOWORD(lParam),
        HIWORD(lParam)
    };
}


} // namespace

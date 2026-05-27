#include "NativeApi.h"

#include "WinApi/ImageLoader/ImageLoader.h"


namespace Blade::Backend {

namespace {

    auto GetWindowStyle(
        HWND hwnd
    ) -> DWORD
    {
        return static_cast<DWORD>(
            GetWindowLongPtr(
                hwnd,
                GWL_STYLE
            )
        );
    }

    auto GetWindowExStyle(
        HWND hwnd
    ) -> DWORD
    {
        return static_cast<DWORD>(
            GetWindowLongPtr(
                hwnd,
                GWL_EXSTYLE
            )
        );
    }

    auto ToOuterSize(
        HWND hwnd,
        const Api::Size& clientSize
    ) -> Api::Size
    {
        RECT rect{
            0,
            0,
            clientSize.width,
            clientSize.height
        };

        AdjustWindowRectEx(
            &rect,
            GetWindowStyle(hwnd),
            FALSE,
            GetWindowExStyle(hwnd)
        );

        return {
            rect.right - rect.left,
            rect.bottom - rect.top
        };
    }

} // namespace


auto NativeApi::SetParent(HWND hwnd, HWND hwndParent) -> HWND
{
    return ::SetParent(hwnd, hwndParent);
}

auto NativeApi::GetParent(HWND hwnd) -> HWND
{
    return ::GetParent(hwnd);
}

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
    SetWindowPos(
        hwnd,
        nullptr,
        0,
        0,
        size.width,
        size.height,
        SWP_NOMOVE |
        SWP_NOZORDER
    );
}

auto NativeApi::SetClientSize(
    HWND hwnd,
    const Api::Size& size
) -> void
{
    SetSize(
        hwnd,
        ToOuterSize(
            hwnd,
            size
        )
    );
}

auto NativeApi::ClientToWindowSize(HWND hwnd, const Api::Size& clientSize) -> Api::Size
{
    return ToOuterSize(hwnd, clientSize);
}

auto NativeApi::SetRect(
    HWND hwnd,
    const Api::Rect& rect
) -> void
{
    SetWindowPos(
        hwnd,
        nullptr,
        rect.x,
        rect.y,
        rect.width,
        rect.height,
        SWP_NOZORDER |
        SWP_NOACTIVATE
    );
}

auto NativeApi::SetClientRect(
    HWND hwnd,
    const Api::Rect& rect
) -> void
{
    SetRect(
        hwnd,
        {
            rect.position(),
            ToOuterSize(
                hwnd,
                rect.size()
            )
        }
    );
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

auto NativeApi::BringToFront(HWND hwnd) -> void
{
    SetWindowPos(
        hwnd,
        HWND_TOP,
        0,
        0,
        0,
        0,
        SWP_NOMOVE |
        SWP_NOSIZE |
        SWP_NOACTIVATE
    );

    RedrawWindow(
        hwnd,
        nullptr,
        nullptr,
        RDW_INVALIDATE |
        RDW_UPDATENOW |
        RDW_ALLCHILDREN
    );
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

auto NativeApi::SetFont(HWND hwnd, HFONT font) -> void
{
    SendMessageW(hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}

auto NativeApi::GetFont(HWND hwnd) -> HFONT
{
    return (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);
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

auto NativeApi::SetVisible(HWND hwnd, bool visible) -> void
{
    Show(hwnd, visible ? SW_SHOW : SW_HIDE);

    if (visible)
    {
        Update(hwnd);
    }
}

auto NativeApi::Update(HWND hwnd) -> void
{
    UpdateWindow(hwnd);
}

auto NativeApi::Destroy(HWND hwnd) -> void
{
    DestroyWindow(hwnd);
}

auto NativeApi::GetScreenSize() -> Api::Size
{
    return {
        .width = GetSystemMetrics(SM_CXSCREEN),
        .height = GetSystemMetrics(SM_CYSCREEN),
    };
}

auto NativeApi::GetSizeFromLParam(
    LPARAM lParam
) -> Api::Size
{
    return {
        LOWORD(lParam),
        HIWORD(lParam)
    };
}

auto NativeApi::SetIcon(HWND hwnd, const Api::Text& icon) -> HICON
{
    auto bigIcon = ImageLoader::LoadIcon(icon, 32, 32);
    auto smallIcon = ImageLoader::IsIcon(icon) ? ImageLoader::LoadIcon(icon, 16, 16) : CopyIcon(bigIcon);

    if (bigIcon) SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(bigIcon));
    if (smallIcon) SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(smallIcon));

    return bigIcon;
}

auto NativeApi::SetStyle(HWND hwnd, DWORD style, int redraw) -> void
{
    SendMessage(hwnd, BM_SETSTYLE, (WPARAM)style, (LPARAM)redraw);
}


} // namespace

#pragma once

#include <windows.h>

#include "Common/Point.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade::Backend {


class NativeApi
{
public:
    /// @brief
    ///
    /// If hwndParent == NULL, the window becomes a top-level window (parented to the desktop).
    /// If hwndParent == HWND_MESSAGE, the window becomes a message-only window
    ///
    /// @param hwnd
    /// @param hwndParent
    /// @return previous parent window
    /// on failure: Returns NULL. Detailed error info can be found by calling GetLastError
    static auto SetParent(
        HWND hwnd,
        HWND hwndParent
    ) -> HWND;

    static auto GetParent(
        HWND hwnd
    ) -> HWND;

    static auto SetTitle(
        HWND hwnd,
        const Api::Text& text
    ) -> void;

    static auto GetTitle(
        HWND hwnd
    ) -> Api::Text;

    static auto SetSize(
        HWND hwnd,
        const Api::Size& size
    ) -> void;

    static auto SetClientSize(
        HWND hwnd,
        const Api::Size& size
    ) -> void;

    static auto SetRect(
        HWND hwnd,
        const Api::Rect& rect
    ) -> void;

    static auto SetClientRect(
        HWND hwnd,
        const Api::Rect& rect
    ) -> void;

    static auto GetSize(
        HWND hwnd
    ) -> Api::Size;

    // TODO combine set size+postion
    static auto SetPosition(
        HWND hwnd,
        const Api::Point& position
    ) -> void;

    static auto BringToFront(
        HWND hwnd
    ) -> void;

    static auto GetPosition(
        HWND hwnd
    ) -> Api::Point;

    static auto SetFont(
        HWND hwnd,
        HFONT font
    ) -> void;

    static auto GetFont(
        HWND hwnd
    ) -> HFONT;

    static auto Show(
        HWND hwnd,
        int cmdShow = SW_SHOW
    ) -> void;

    static auto Update(
        HWND hwnd
    ) -> void;

    static auto Destroy(
        HWND hwnd
    ) -> void;

    static auto GetScreenSize() -> Api::Size;

    static auto GetSizeFromLParam(
        LPARAM lParam
    ) -> Api::Size;

    static auto SetIcon(HWND hwnd, const Api::Text& icon) -> HICON;
};


} // namespace

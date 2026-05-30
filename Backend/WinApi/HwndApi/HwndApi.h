#pragma once

#include <windows.h>

#include "Common/Point.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade::Backend {

class HwndApi
{
public:
    static auto SetParent(HWND hwnd, HWND hwndParent) -> HWND;
    static auto GetParent(HWND hwnd) -> HWND;

    static auto SetTitle(HWND hwnd, const Api::Text& text) -> void;
    static auto GetTitle(HWND hwnd) -> Api::Text;

    static auto SetSize(HWND hwnd, const Api::Size& size) -> void;
    static auto SetClientSize(HWND hwnd, const Api::Size& size) -> void;

    static auto ClientToWindowSize(HWND hwnd, const Api::Size& clientSize) -> Api::Size;

    static auto SetRect(HWND hwnd, const Api::Rect& rect) -> void;
    static auto SetClientRect(HWND hwnd, const Api::Rect& rect) -> void;
    static auto GetClientRect(HWND hwnd) -> Api::Rect;
    static auto GetSize(HWND hwnd) -> Api::Size;
    static auto SetPosition(HWND hwnd, const Api::Point& position) -> void;
    static auto BringToFront(HWND hwnd) -> void;
    static auto GetPosition(HWND hwnd) -> Api::Point;

    static auto SetFont(HWND hwnd, HFONT font) -> void;
    static auto GetFont(HWND hwnd) -> HFONT;

    static auto SetRoundedRegion(HWND hwnd, const Api::Size& size, int radius) -> void;
    static auto Show(HWND hwnd, int cmdShow = SW_SHOW) -> void;
    static auto SetVisible(HWND hwnd, bool visible) -> void;
    static auto Invalidate(HWND hwnd) -> void;
    static auto Update(HWND hwnd) -> void;
    static auto Close(HWND hwnd) -> void;
    static auto Destroy(HWND hwnd) -> void;

    static auto GetSizeFromLParam(LPARAM lParam) -> Api::Size;
};

} // namespace

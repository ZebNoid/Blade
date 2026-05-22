#pragma once

#include <windows.h>

#include "Common/Point.h"
#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade::Backend {


class NativeApi
{
public:
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

    static auto GetSize(
        HWND hwnd
    ) -> Api::Size;

    // TODO combine set size+postion
    static auto SetPosition(
        HWND hwnd,
        const Api::Point& position
    ) -> void;

    static auto GetPosition(
        HWND hwnd
    ) -> Api::Point;

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

    static auto ScreenSize() -> Api::Size;
};


} // namespace

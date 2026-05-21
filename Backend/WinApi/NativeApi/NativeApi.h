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

    static auto SetSize(
        HWND hwnd,
        const Api::Size& size
    ) -> void;

    static auto SetPosition(
        HWND hwnd,
        const Api::Point& position
    ) -> void;
};


} // namespace

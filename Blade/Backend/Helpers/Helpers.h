#pragma once

#include <windows.h>
#include <windowsx.h>

#include "Props/Common/Point.h"


namespace Blade {

struct Helpers {};


inline auto MousePosition(const LPARAM lParam) -> Point
{
    return {
        GET_X_LPARAM(lParam),
        GET_Y_LPARAM(lParam)
    };
}

} // namespace

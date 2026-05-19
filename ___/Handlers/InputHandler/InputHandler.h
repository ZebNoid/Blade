#pragma once

#include <windows.h>

#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


class InputHandler
{
public:
    static auto Handle(
        WinWindow& window,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
    ) -> LRESULT;
};


} // namespace

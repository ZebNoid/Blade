#pragma once

#include <windows.h>

#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


class CommandHandler
{
public:
    static auto Handle(
        WinWindow& window,
        WPARAM wParam,
        LPARAM lParam
    ) -> LRESULT;

};


} // namespace

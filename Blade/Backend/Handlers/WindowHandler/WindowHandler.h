#pragma once

#include <windows.h>

#include "../../../../Backend/WinWindow/WinWindow.h"


namespace Blade::Backend::WinApi {


class WindowHandler
{
public:
    static auto Handle(WinWindow& window, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
};


} // namespace

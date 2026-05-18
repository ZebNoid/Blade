#pragma once

#include <windows.h>

#include "../../../../Backend/WinWindow/WinWindow.h"


namespace Blade::Backend::WinApi {


class PaintHandler
{
public:
    static auto Handle(WinWindow& window, WPARAM wParam, LPARAM lParam) -> LRESULT;
};


} // namespace

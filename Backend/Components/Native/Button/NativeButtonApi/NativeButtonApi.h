#pragma once

#include <windows.h>

namespace Blade::Backend {

class NativeButtonApi
{
public:
    static auto SetStyle(HWND hwnd, DWORD style, int redraw = TRUE) -> void;
};

} // namespace Blade::Backend

#pragma once

#include <windows.h>

namespace Blade::Backend {

class ThemeApi
{
public:
    static auto WindowBrush() -> HBRUSH;
    static auto WindowTextColor() -> COLORREF;
};

} // namespace Blade::Backend

#include "ThemeApi.h"

namespace Blade::Backend {

auto ThemeApi::WindowBrush() -> HBRUSH
{
    return GetSysColorBrush(COLOR_WINDOW);
}

auto ThemeApi::WindowTextColor() -> COLORREF
{
    return GetSysColor(COLOR_WINDOWTEXT);
}

} // namespace Blade::Backend

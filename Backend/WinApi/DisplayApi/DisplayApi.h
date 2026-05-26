#pragma once

#include <windows.h>

#include "Common/Rect.h"


namespace Blade::Backend {

class DisplayApi
{
public:
    static auto Count() -> int;
    static auto WorkArea(int monitor = 0) -> Api::Rect;
    static auto DesktopRect() -> Api::Rect;
};

} // namespace Blade::Backend

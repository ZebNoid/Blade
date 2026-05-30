#pragma once

#include <windows.h>

#include "Geometry/Rect.h"


namespace Blade::Backend {

class DisplayApi
{
public:
    static auto InitDpi() -> void;

    static auto Count() -> int;
    static auto WorkArea(int monitor = 0) -> Api::Rect;
    static auto DesktopRect() -> Api::Rect;
};

} // namespace Blade::Backend

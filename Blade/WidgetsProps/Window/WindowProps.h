#pragma once

#include <string>

#include "WidgetsProps/Common/Point.h"
#include "WidgetsProps/Common/Size.h"
#include "WidgetsProps/Common/Thickness.h"


namespace Blade {


struct WindowProps
{
    std::wstring title = L"Blade"; // TODO later
    // TODO remember size/position
    // TODO minSize / maxSize
    Size size{800, 600};
    // TODO default by system
    Point position{-1 , -1 };
    // TODO separate prop struct or enum
    bool resizable = true;
    bool minimizable = true;
    bool maximizable = true;

    bool center = true;

    bool visible = true;
};


} // namespace

#pragma once

#include <string>

#include "Props/Common/Point.h"
#include "Props/Common/Size.h"
#include "Props/Common/Thickness.h"


namespace Blade {


struct WindowProps
{
    std::string title = "Blade";
    // TODO remember size/position
    // TODO minSize / maxSize
    Size size{800, 600};
    // TODO remove windows default
    Point position{CW_USEDEFAULT, CW_USEDEFAULT};
    // TODO separate prop struct or enum
    bool resizable = true;
    bool minimizable = true;
    bool maximizable = true;

    bool center = true;

    bool visible = true;
};


} // namespace

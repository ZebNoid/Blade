#pragma once
#include <string>

#include "Props/Common/Thickness.h"
#include "Props/Common/Size.h"


struct WindowProps
{
    std::string title = "Blade";
    Size size{800, 600};
    Thickness padding{};

    bool resizable = true;
    bool minimizable = true;
    bool maximizable = true;

    bool center = true;

    bool visible = true;
};

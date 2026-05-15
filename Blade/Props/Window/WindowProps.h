#pragma once
#include <string>
#include "Props/Common/Thickness.h"
#include "Props/Common/Size.h"

struct WindowProps
{
    std::string title;
    Size size{300, 300}; // TODO
    Thickness padding{};

    bool resizable = true;
    bool minimizable = true;
    bool maximizable = true;

    bool center = true;
};

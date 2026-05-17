#pragma once

#include "Thickness.h"


namespace Blade {


struct LayoutProps
{
    Thickness margin{};
    Thickness padding{};
    
    int flex = 0;
};


} // namespace

#pragma once
#include "Thickness.h"


namespace Blade::Api {

struct LayoutProps
{
    Thickness margin{};
    Thickness padding{};
    
    int flex = 1;
};


} // namespace

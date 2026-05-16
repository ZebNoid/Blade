#pragma once

#include "Props/Common/LayoutProps.h"
#include "Props/Common/TextAlign.h"


namespace Blade {


struct LabelProps
{
    LayoutProps layout;
    // bit mask?
    TextAlign textAlign = TextAlign::Center;
    int maxLines = 1;
};


} // namespace

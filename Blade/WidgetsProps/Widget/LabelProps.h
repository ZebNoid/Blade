#pragma once

#include "WidgetsProps/Common/LayoutProps.h"
#include "WidgetsProps/Common/TextAlign.h"


namespace Blade {


struct LabelProps
{
    LayoutProps layout;
    // bit mask?
    TextAlign textAlign = TextAlign::Center;
    int maxLines = 1;
};


} // namespace

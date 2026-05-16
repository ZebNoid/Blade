#pragma once

#include "Props/Common/LayoutProps.h"
#include "Props/Common/TextAlign.h"


namespace Blade {


struct LabelProps
{
    LayoutProps layout;
    TextAlign textAlign = TextAlign::Start;
    int maxLines = 1;
};


} // namespace

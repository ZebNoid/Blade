#pragma once

#include "Props/Common/CrossAxisAlignment.h"
#include "Props/Common/LayoutProps.h"
#include "Props/Common/MainAxisAlignment.h"


namespace Blade {


struct RowProps
{
    int gap = 0;
    LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;
};


} // namespace

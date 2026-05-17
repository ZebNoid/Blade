#pragma once

#include "WidgetsProps/Common/CrossAxisAlignment.h"
#include "WidgetsProps/Common/LayoutProps.h"
#include "WidgetsProps/Common/MainAxisAlignment.h"


namespace Blade {


struct RowProps
{
    int gap = 0;
    LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;
};


} // namespace

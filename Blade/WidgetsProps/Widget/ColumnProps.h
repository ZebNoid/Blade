#pragma once

#include "WidgetsProps/Common/CrossAxisAlignment.h"
#include "WidgetsProps/Common/LayoutProps.h"
#include "WidgetsProps/Common/MainAxisAlignment.h"


namespace Blade {


struct ColumnProps
{
    int gap = 0;
    LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;
};


} // namespace

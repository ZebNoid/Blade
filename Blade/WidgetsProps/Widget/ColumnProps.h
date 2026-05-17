#pragma once

#include "WidgetsProps/LayoutProps/CrossAxisAlignment.h"
#include "WidgetsProps/LayoutProps/LayoutProps.h"
#include "WidgetsProps/LayoutProps/MainAxisAlignment.h"


namespace Blade {


struct ColumnProps
{
    int gap = 0;
    LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;
};


} // namespace

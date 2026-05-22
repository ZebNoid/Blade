#pragma once

#include "Common/LayoutProps.h"
#include "../../../Props/LayoutProps/CrossAxisAlignment.h"
#include "../../../Props/LayoutProps/MainAxisAlignment.h"


namespace Blade {


struct ColumnProps
{
    int gap = 0;
    Api::LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;
};


} // namespace

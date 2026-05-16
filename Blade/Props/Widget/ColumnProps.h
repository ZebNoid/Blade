#pragma once

#include "Props/Common/Alignment.h"
#include "Props/Common/LayoutProps.h"


namespace Blade {


struct ColumnProps
{
    int spacing = 0; // TODO gap?
    Alignment mainAxisAlignment = Alignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Stretch;
    LayoutProps layout{};
};


} // namespace

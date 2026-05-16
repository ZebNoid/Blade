#pragma once

#include "Props/Common/Alignment.h"
#include "Props/Common/LayoutProps.h"


namespace Blade {


struct RowProps
{
    int spacing = 0;
    // Alignment mainAxisAlignment = Alignment::Start;
    // CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Stretch;
    LayoutProps layout{};
};


} // namespace

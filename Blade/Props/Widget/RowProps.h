#pragma once
#include "../Common/LayoutProps.h"
#include "../Common/Alignment.h"

struct RowProps
{
    int spacing = 0;
    // Alignment mainAxisAlignment = Alignment::Start;
    // CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Stretch;
    LayoutProps layout{};
};

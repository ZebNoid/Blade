#pragma once
#include <any>
#include <string>
#include <vector>

#include "Common/Common.h"


namespace Blade::Api {


struct WidgetTree
{
    Id id = 0;

    Api::Text type;   // "Window", "Button", "Column"

    std::any props;      // или typed variant later
    std::any events;
    std::any custom;

    std::vector<WidgetTree> children;
};

} // namespace
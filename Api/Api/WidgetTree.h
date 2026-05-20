#pragma once
#include <any>
#include <string>
#include <vector>

#include "Common/Types.h"


namespace Blade::Api {


// TODO move to Blade?
struct WidgetTree
{
    Api::Id id = 0;

    Api::Text type; // "Window", "Button", "Column"

    std::any props; // или typed variant later
    std::any events;
    std::any custom;

    std::vector<WidgetTree> children;
};

} // namespace

#pragma once

#include <string>
#include <vector>

#include "Common/Property.h"
#include "Common/Types.h"


namespace Blade {


// TODO move to Blade?
struct WidgetTree
{
    Api::Id id = 0;

    Api::Text type; // "Window", "Button", "Column"

    // backend
    Api::PropertyMap props;
    Api::EventMap events;
    // TODO map std::any custom; ?
    Api::PropertyValue custom;
    // std::unordered_map<Api::Text, Api::PropertyValue> custom;

    std::vector<WidgetTree> children;
};

} // namespace

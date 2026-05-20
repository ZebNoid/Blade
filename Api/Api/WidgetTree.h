#pragma once
#include <any>
#include <string>
#include <vector>

#include "Common/Property.h"
#include "Common/Types.h"


namespace Blade::Api {


// TODO move to Blade?
struct WidgetTree
{
    Api::Id id = 0;

    Api::Text type; // "Window", "Button", "Column"

    Api::PropertyMap props;
    Api::EventMap events;
    // TODO std::any custom; ?
    Api::PropertyValue custom;

    std::vector<WidgetTree> children;
};

} // namespace

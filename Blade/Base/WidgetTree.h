#pragma once

#include <string>
#include <vector>

#include "Common/Property.h"
#include "Common/Types.h"
#include "Runtime/LayoutEngine/Data/LayoutType.h"


namespace Blade {


// TODO move to Blade?
struct WidgetTree
{
    Api::Id id = 0;

    Api::Text type; // "Window", "Button", "Column"

    LayoutType layoutType = LayoutType::None;

    // backend
    Api::PropertyMap props;
    Api::EventMap events;

    std::vector<WidgetTree> children;
};

} // namespace

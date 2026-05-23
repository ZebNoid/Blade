#pragma once

#include <string>
#include <vector>

#include "Common/Property.h"
#include "Common/Types.h"
#include "Runtime/LayoutEngine/Data/LayoutType.h"
#include "Runtime/LayoutEngine/Data/LayoutData.h"
#include "Runtime/Normalize/NormalizedProps.h"


namespace Blade {


// TODO move to Blade?
struct WidgetTree
{
    Api::Id id = 0;

    Api::Text type; // "Window", "Button", "Column"

    LayoutType layoutType = LayoutType::None;

    BackendProps backend;
    LayoutData layout;

    Api::EventMap events;

    std::vector<WidgetTree> children;
};

} // namespace

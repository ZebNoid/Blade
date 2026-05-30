#pragma once

#include <string>
#include <vector>

#include "Common/Lifetime.h"
#include "Common/Modifier.h"
#include "Common/Property.h"
#include "Common/Types.h"
#include "Runtime/LayoutEngine/Data/LayoutType.h"
#include "Runtime/LayoutEngine/Data/LayoutData.h"
#include "Runtime/Normalize/NormalizedProps.h"


namespace Blade {


struct WidgetTree
{
    Api::Id id = 0;

    Api::Text type; // "Window", "Button", "Column"

    LayoutType layoutType = LayoutType::None;
    Api::Lifetime lifetime = Api::Lifetime::Owner;

    BackendProps backend;
    LayoutData layout;
    Api::Modifier modifier;

    Api::EventMap events;

    std::vector<WidgetTree> children;
    std::vector<WidgetTree> overlays;
};

} // namespace

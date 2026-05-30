#pragma once

#include <vector>

#include "LayoutData.h"
#include "Common/LayoutProps.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "Widget/WidgetType.h"
#include "LayoutType.h"


namespace Blade {

struct LayoutNode
{
    Api::Id id = Api::InvalidId;

    Api::WidgetType type = Api::WidgetTypes::Unknown;

    LayoutType layoutType = LayoutType::None;

    LayoutData layout;

    Api::Size desiredSize{};

    Api::Rect rect{};

    std::vector<LayoutNode> children;
};


} // namespace

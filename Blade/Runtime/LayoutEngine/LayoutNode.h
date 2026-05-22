#pragma once

#include <vector>

#include "Common/LayoutProps.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade {

struct LayoutNode
{
    Api::Id id = Api::InvalidId;

    Api::Text type; // TODO ?

    Api::LayoutProps layout;

    Api::Size desiredSize{};

    Api::Rect rect{};

    bool isNative = false;

    std::vector<LayoutNode> children;
};


} // namespace
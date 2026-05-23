#pragma once

#include <vector>

#include "LayoutData.h"
#include "Common/LayoutProps.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "LayoutType.h"


namespace Blade {

struct LayoutNode
{
    Api::Id id = Api::InvalidId;

    Api::Text type; // TODO ?

    LayoutType layoutType = LayoutType::None;

    LayoutData layout;

    Api::Size desiredSize{};

    Api::Rect rect{};

    bool isNative = false; // TODO node db from backend

    std::vector<LayoutNode> children;
};


} // namespace

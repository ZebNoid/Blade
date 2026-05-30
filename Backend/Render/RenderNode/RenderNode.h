#pragma once

#include "Geometry/Rect.h"
#include "Common/Types.h"
#include "Render/RenderOp.h"

namespace Blade::Backend {

struct RenderNode
{
    Api::Id id = Api::InvalidId;
    Api::Id root = Api::InvalidId;
    Api::Id parent = Api::InvalidId;
    int order = 0;
    Api::Rect rect{};
    Api::RenderStates render{};
    Api::WidgetState state = Api::WidgetState::Normal;
    bool visible = true;
};

} // namespace Blade::Backend

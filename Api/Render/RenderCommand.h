#pragma once

#include "Common/Rect.h"
#include "Common/Types.h"
#include "Render/RenderCommandType.h"
#include "Render/RenderOp.h"

namespace Blade::Api {

struct RenderCommand
{
    Api::RenderCommandType command = Api::RenderCommandType::Create;
    Api::Id id = Api::InvalidId;
    Api::Id root = Api::InvalidId;
    Api::Id parent = Api::InvalidId;
    int order = 0;
    Api::Rect rect{};
    Api::RenderStates render{};
};

} // namespace Blade::Api

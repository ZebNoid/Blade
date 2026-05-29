#pragma once

#include "Base/WidgetTree.h"

namespace Blade {

struct MaterializerState
{
    const std::vector<WidgetTree>* contextMenus = nullptr;
    Api::Id dropTarget = Api::InvalidId;
};

} // namespace Blade

#pragma once

#include "Base/WidgetTree.h"
#include "Common/MenuData.h"

namespace Blade {

class MenuMaterializer
{
public:
    static auto Build(const std::vector<WidgetTree>* overlays) -> Api::ContextMenus;
};

} // namespace Blade

#pragma once

#include "Base/WidgetTree.h"
#include "Menu/MenuData.h"

namespace Blade {

class MenuMaterializer
{
public:
    static auto Build(const std::vector<WidgetTree>* overlays) -> Api::ContextMenus;
};

} // namespace Blade

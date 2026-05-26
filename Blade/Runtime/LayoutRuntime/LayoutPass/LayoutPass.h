#pragma once

#include "Base/WidgetTree.h"
#include "Common/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {

class LayoutPass
{
public:
    static auto Compute(const WidgetTree& tree, const Api::Size& available) -> LayoutNode;
};

} // namespace Blade

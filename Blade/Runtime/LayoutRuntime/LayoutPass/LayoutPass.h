#pragma once

#include "Base/WidgetTree.h"
#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade::Layout::Pass {

auto Compute(const WidgetTree& tree, const Api::Size& available) -> LayoutNode;

} // namespace Blade::Layout::Pass

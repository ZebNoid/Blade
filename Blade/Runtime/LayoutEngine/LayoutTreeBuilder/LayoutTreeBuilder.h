#pragma once
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"

namespace Blade::Layout::TreeBuilder {

auto Build(const WidgetTree& tree) -> LayoutNode;

} // namespace Blade::Layout::TreeBuilder

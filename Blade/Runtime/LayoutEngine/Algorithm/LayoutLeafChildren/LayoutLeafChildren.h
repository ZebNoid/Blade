#pragma once

#include "Geometry/Rect.h"
#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade::LayoutLeafChildren {

auto Measure(LayoutNode& node) -> Api::Size;
auto Arrange(LayoutNode& node, const Api::Rect& contentRect) -> void;

} // namespace Blade::LayoutLeafChildren

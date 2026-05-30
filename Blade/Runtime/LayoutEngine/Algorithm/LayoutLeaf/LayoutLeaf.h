#pragma once

#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutContext.h"


namespace Blade::Layout::Leaf {

auto Measure(LayoutContext& ctx) -> Api::Size;
auto Arrange(LayoutContext& ctx) -> void;

} // namespace Blade::Layout::Leaf

#pragma once

#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutContext.h"
#include "Runtime/LayoutEngine/Geometry/LayoutAxis.h"


namespace Blade::Layout::Linear {

auto Measure(LayoutContext& ctx, LayoutAxis axis) -> Api::Size;
auto Arrange(LayoutContext& ctx, LayoutAxis axis) -> void;

} // namespace Blade::Layout::Linear

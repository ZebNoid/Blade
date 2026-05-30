#pragma once

#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutContext.h"
#include "Runtime/LayoutEngine/Geometry/LayoutAxis.h"


namespace Blade {

class LayoutLinear
{
public:
    static auto Measure(LayoutContext& ctx, LayoutAxis axis) -> Api::Size;
    static auto Arrange(LayoutContext& ctx, LayoutAxis axis) -> void;
};

} // namespace Blade

#pragma once

#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutContext.h"


namespace Blade {

class LayoutRow
{
public:
    static auto Measure(LayoutContext& ctx) -> Api::Size;
    static auto Arrange(LayoutContext& ctx) -> void;
};

} // namespace Blade

#pragma once

#include "Runtime/LayoutEngine/Data/LayoutContext.h"

namespace Blade {

class LayoutVirtual
{
public:
    static auto Measure(LayoutContext& ctx) -> Api::Size;
    static auto Arrange(LayoutContext& ctx) -> void;
};

} // namespace Blade

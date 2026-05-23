#pragma once
#include "Runtime/LayoutEngine/Data/LayoutContext.h"


namespace Blade {


class LayoutEngine
{
public:
    static auto Measure(
        LayoutContext& ctx
    ) -> Api::Size;

    static auto Arrange(
        LayoutContext& ctx
    ) -> void;
};


} // namespace

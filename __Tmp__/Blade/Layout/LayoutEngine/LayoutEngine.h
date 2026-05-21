#pragma once

#include "Layout/LayoutContext/LayoutContext.h"


namespace Blade {


class LayoutEngine
{
public:
    static auto Measure(const LayoutContext& ctx) -> Size;

    static auto Arrange(const LayoutContext& ctx) -> void;
};


} // namespace

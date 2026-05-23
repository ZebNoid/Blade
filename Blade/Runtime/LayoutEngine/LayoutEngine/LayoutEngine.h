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


    static auto MeasureLeaf(
        LayoutContext& ctx
    ) -> Api::Size;

    static auto ArrangeLeaf(
        LayoutContext& ctx
    ) -> void;

    static auto MeasureColumn(
        LayoutContext& ctx
    ) -> Api::Size;

    static auto ArrangeColumn(
        LayoutContext& ctx
    ) -> void;
};


} // namespace

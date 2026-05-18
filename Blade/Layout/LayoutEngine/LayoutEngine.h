#pragma once
#include "LayoutType.h"
#include "Layout/FlexLayout/FlexDirection.h"


namespace Blade {


class LayoutEngine
{
public:
    static auto Measure(
        LayoutType type,
        FlexDirection direction,
        const std::vector<std::unique_ptr<Widget>>& children,
        const LayoutProps& layout,
        int gap,
        Size available
    ) -> Size;

    static auto Arrange(
        LayoutType type,
        FlexDirection direction,
        const std::vector<std::unique_ptr<Widget>>& children,
        const LayoutProps& layout,
        MainAxisAlignment mainAxisAlignment,
        CrossAxisAlignment crossAxisAlignment,
        int gap,
        Rect rect
    ) -> void;
};


} // namespace

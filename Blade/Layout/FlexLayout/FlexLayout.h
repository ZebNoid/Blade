#pragma once

#include <memory>
#include <vector>

#include "FlexDirection.h"
#include "Props/Common/CrossAxisAlignment.h"
#include "Props/Common/LayoutProps.h"
#include "Props/Common/MainAxisAlignment.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class FlexLayout
{
public:
    static auto Measure(
        FlexDirection direction,
        const std::vector<std::unique_ptr<Widget>>& children,
        const LayoutProps& layout,
        int gap,
        Size available
    ) -> Size;

    static auto Arrange(
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

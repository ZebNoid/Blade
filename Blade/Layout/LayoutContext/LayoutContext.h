#pragma once
#include <memory>
#include <vector>

#include "Layout/FlexLayout/FlexDirection.h"
#include "Layout/LayoutEngine/LayoutType.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsProps/LayoutProps/CrossAxisAlignment.h"
#include "WidgetsProps/LayoutProps/MainAxisAlignment.h"


namespace Blade {


struct LayoutContext
{
    LayoutType type;
    FlexDirection direction = FlexDirection::Column;

    const std::vector<std::unique_ptr<Widget>>* children = nullptr;

    const LayoutProps* layout = nullptr;

    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;

    int gap = 0;

    Size available{};
    Rect rect{};
};


} // namespace

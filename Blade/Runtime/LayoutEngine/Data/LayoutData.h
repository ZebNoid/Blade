#pragma once
#include "Geometry/Point.h"
#include "Geometry/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutBox.h"
#include "Props/LayoutProps/CrossAxisAlignment.h"
#include "Props/LayoutProps/MainAxisAlignment.h"

namespace Blade {

struct LayoutData
{
    LayoutBox box;
    Api::Size size{};
    Api::Point position{};
    int gap = 0;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Stretch;
};

} // namespace

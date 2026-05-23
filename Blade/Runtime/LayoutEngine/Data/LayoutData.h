#pragma once
#include "Common/LayoutProps.h"
#include "Common/Point.h"
#include "Common/Size.h"

namespace Blade {

struct LayoutData
{
    Api::LayoutProps layout;
    Api::Size size{};
    Api::Point position{};
    int gap = 0;
};

} // namespace

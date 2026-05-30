#pragma once

#include "Geometry/Point.h"

namespace Blade::Api {

enum class WindowAnchor
{
    Manual,

    TopLeft,
    TopCenter,
    TopRight,
    TopFill,

    CenterLeft,
    Center,
    CenterRight,
    CenterHorizontalFill,

    BottomLeft,
    BottomCenter,
    BottomRight,
    BottomFill,

    LeftFill,
    CenterVerticalFill,
    RightFill,
    Fill
};

struct WindowPlacementProps
{
    WindowAnchor anchor = WindowAnchor::Manual;
    Api::Point offset{};
    int monitor = 0;
};

} // namespace Blade::Api

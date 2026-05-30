#pragma once

#include "Geometry/Thickness.h"

namespace Blade {

struct LayoutBox
{
    Api::Thickness padding{};
    int flex = 0;
    Api::Size minSize{};
    Api::Size maxSize{};
};

} // namespace Blade

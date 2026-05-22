#pragma once

#include "LayoutNode.h"


namespace Blade {


struct LayoutContext
{
    LayoutNode* node = nullptr;

    Api::Size available{};

    Api::Rect rect{};
};


} // namespace
#pragma once

#include "Common/Props.h"
#include "Runtime/Normalize/PropsVisitor.h"

namespace Blade {

struct LabelProps
{
    Api::LayoutProps layout{};
    Api::Size size{120, 24};

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Layout, layout);
        v.set(Api::Props::Size, size);
    }
};

} // namespace Blade

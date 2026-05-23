#pragma once

#include "Common/LayoutProps.h"
#include "Runtime/Normalize/PropsVisitor.h"


namespace Blade {

struct StackProps
{
    Api::LayoutProps layout;

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Layout, layout);
    }
};

} // namespace Blade

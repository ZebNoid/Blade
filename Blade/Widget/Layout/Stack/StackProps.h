#pragma once

#include "Common/LayoutProps.h"
#include "Runtime/Normalize/PropertyVisitor.h"


namespace Blade {

struct StackProps
{
    Api::LayoutProps layout;

    auto visit(PropertyVisitor& v) const -> void
    {
        v.set(Api::Props::Layout, layout);
    }
};

} // namespace Blade

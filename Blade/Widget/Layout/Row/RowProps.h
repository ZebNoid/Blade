#pragma once

#include "Common/LayoutProps.h"
#include "Props/LayoutProps/CrossAxisAlignment.h"
#include "Props/LayoutProps/MainAxisAlignment.h"
#include "Runtime/Normalize/PropsVisitor.h"


namespace Blade {

struct RowProps
{
    int gap = 0;
    Api::LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Stretch;

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Gap, gap);
        v.set(Api::Props::Layout, layout);
        v.set(mainAxisAlignment);
        v.set(crossAxisAlignment);
    }
};

} // namespace Blade

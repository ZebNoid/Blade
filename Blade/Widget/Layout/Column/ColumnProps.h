#pragma once

#include "Common/LayoutProps.h"
#include "Props/LayoutProps/CrossAxisAlignment.h"
#include "Props/LayoutProps/MainAxisAlignment.h"


namespace Blade {


struct ColumnProps
{
    int gap = 0;
    Api::LayoutProps layout;
    MainAxisAlignment mainAxisAlignment = MainAxisAlignment::Start;
    CrossAxisAlignment crossAxisAlignment = CrossAxisAlignment::Start;

    auto visit(PropertyVisitor& v) const -> void
    {
        v.set(Api::Props::Gap, gap);
        v.set(Api::Props::Layout, layout);
        // TODO
        // v.setLayout(LayoutEngineKey::Alignment, mainAxisAlignment);
        // v.setLayout(LayoutEngineKey::Alignment, crossAxisAlignment);
    }
};


} // namespace

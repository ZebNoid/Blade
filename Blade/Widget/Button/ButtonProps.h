#pragma once

#include "Runtime/Normalize/PropertyVisitor.h"

#include "Common/Props.h"


namespace Blade {


struct ButtonProps
{
    Api::LayoutProps layout{};
    bool isDefault = false;

    auto visit(PropertyVisitor& v) const -> void
    {
        v.set(Api::Props::Layout, layout);
        v.set(Api::Props::Default, isDefault);
    }
};


}

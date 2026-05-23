#pragma once

#include "Runtime/Normalize/PropertyVisitor.h"

#include "Common/Props.h"


namespace Blade {


struct ButtonProps
{
    Api::LayoutProps layout{};
    Api::Size size{100,50};
    bool isDefault = false;

    auto visit(PropertyVisitor& v) const -> void
    {
        v.set(Api::Props::Layout, layout);
        v.set(Api::Props::Default, isDefault);
        v.set(Api::Props::Size, size);
    }
};


}

#pragma once

#include "Runtime/PropertyVisitor.h"


namespace Blade {


struct ButtonProps
{
    Api::LayoutProps layout{};
    bool isDefault = false;

    auto visit(PropertyVisitor& v) const -> void
    {
        v.set(L"layout", layout);
        v.set(L"isDefault", isDefault);
    }
};


}

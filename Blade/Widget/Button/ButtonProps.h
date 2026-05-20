#pragma once

#include "Common/Common.h"
#include "Runtime/VisitCallback.h"


namespace Blade {


struct ButtonProps
{
    Api::LayoutProps layout{};
    bool isDefault = false;

    auto visit(const VisitFn& v) const -> void
    {
        // v(L"layout", layout);
        v(L"isDefault", isDefault);
    }
};


}

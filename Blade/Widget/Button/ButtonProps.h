#pragma once

#include "Common/Common.h"
#include "Runtime/VisitCallback.h"


namespace Blade {


struct ButtonProps
{
    LayoutProps layout{};
    bool isDefault = false;

    auto visit(const VisitCallback& v) const -> void
    {
        v(L"layout", layout);
        v(L"isDefault", isDefault);
    }
};


}

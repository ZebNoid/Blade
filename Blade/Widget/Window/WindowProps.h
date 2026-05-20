#pragma once

#include "Common/Common.h"
#include "Runtime/VisitCallback.h"


namespace Blade {


struct WindowProps
{
    Api::Text title = L"Blade"; // TODO later
    Api::Size size{800, 600};
    Api::Point position{-1 , -1 };

    auto visit(const VisitFn& v) const -> void
    {
        // v(L"layout", layout);
        v(L"title", title);
        v(L"size", size);
        v(L"position", position);
    }
};


} // namespace

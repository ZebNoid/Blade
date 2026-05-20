#pragma once

#include "Common/Point.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "../../Runtime/Normalize/PropertyVisitor.h"


namespace Blade {


struct WindowProps
{
    Api::Text title = L"Blade"; // TODO later
    Api::Size size{800, 600};
    Api::Point position{-1, -1};

    auto visit(PropertyVisitor& v) const -> void
    {
        v.set(L"title", title);
        v.set(L"size", size);
        v.set(L"position", position);
    }
};


} // namespace

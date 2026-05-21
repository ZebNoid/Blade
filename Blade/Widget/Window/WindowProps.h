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
        v.set(Api::Props::Title, title);
        v.set(Api::Props::Size, size);
        v.set(Api::Props::Position, position);
    }
};


} // namespace

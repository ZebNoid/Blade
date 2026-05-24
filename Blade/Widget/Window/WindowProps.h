#pragma once

#include "Common/Point.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "Runtime/Normalize/PropsVisitor.h"


namespace Blade {


struct WindowProps
{
    Api::Text title = L"Blade";
    Api::Size size{800,600}; // TODO default?
    Api::Point position{-1, -1}; // TODO default

    // TODO no caption
    // TODO start absolute or relative
    // TODO start align

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Title, title);
        v.set(Api::Props::Size, size);
        v.set(Api::Props::Position, position);
    }
};


} // namespace

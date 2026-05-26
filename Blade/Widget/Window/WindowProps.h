#pragma once

#include "Common/CaptionProps.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "Fabric/WindowPlacement.h"
#include "Runtime/Normalize/PropsVisitor.h"


namespace Blade {


struct WindowProps
{
    Api::Text title = L"Blade";
    Api::Size size{800,600}; // TODO default?
    bool visible = true;
    Api::CaptionProps caption{};
    Api::WindowPlacementProps placement = Api::WindowPlacement::Default();

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Title, title);
        v.set(Api::Props::Size, size);
        v.set(Api::Props::Placement, placement);
        v.set(Api::Props::Visible, visible);
        v.set(Api::Props::Caption, caption);
    }
};


} // namespace

#pragma once

#include "Common/CaptionProps.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "Common/WindowState.h"
#include "Fabric/WindowPlacement.h"
#include "Runtime/Normalize/PropsVisitor.h"


namespace Blade {


struct WindowProps
{
    Api::Text title = L"Blade";
    Api::Text icon{};
    Api::Size size{800,600}; // TODO Fabric or Constant WindowSize::DefaultSize
    bool visible = true;
    bool resizable = true;
    bool topMost = false;
    bool taskbar = true;
    Api::Size minSize{}; // TODO Fabric or Constant WindowSize::DefaultMinSize
    Api::Size maxSize{};
    Api::CaptionProps caption{};
    Api::WindowPlacementProps placement = Api::WindowPlacement::Default();
    Api::WindowState state = Api::WindowState::Normal;

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Title, title);
        v.set(Api::Props::Icon, icon);
        v.set(Api::Props::Size, size);
        v.set(Api::Props::Placement, placement);
        v.set(Api::Props::Visible, visible);
        v.set(Api::Props::Resizable, resizable);
        v.set(Api::Props::TopMost, topMost);
        v.set(Api::Props::Taskbar, taskbar);
        v.set(Api::Props::MinSize, minSize);
        v.set(Api::Props::MaxSize, maxSize);
        v.set(Api::Props::Caption, caption);
        v.set(Api::Props::State, state);
    }
};


} // namespace

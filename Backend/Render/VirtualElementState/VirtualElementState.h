#pragma once

#include "Render/RenderOp.h"

namespace Blade::Backend {

struct VirtualElementEvents
{
    bool click = false;
    bool focus = false;
    bool drop = false;
};

struct VirtualElementState
{
    bool visible = true;
    bool pressed = false;
    bool focused = false;
    bool hovered = false;
    bool dragOver = false;
};

inline auto VisualState(const VirtualElementState& state) -> Api::WidgetState
{
    if (state.dragOver) return Api::WidgetState::DragOver;
    if (state.pressed) return Api::WidgetState::Pressed;
    if (state.hovered) return Api::WidgetState::Hover;
    if (state.focused) return Api::WidgetState::Focus;
    return Api::WidgetState::Normal;
}

} // namespace Blade::Backend

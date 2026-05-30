#pragma once

#include <variant>
#include <vector>

#include "Common/Color.h"
#include "Common/Modifier.h"

namespace Blade::Api {

struct RenderBackground
{
    Api::Color color{};
};

struct RenderBorderRadius
{
    int radius = 0;
};

struct RenderBorderColor
{
    Api::Color color{};
};

struct RenderTextColor
{
    Api::Color color{};
};

using RenderOp = std::variant<
    Api::RenderBackground,
    Api::RenderBorderRadius,
    Api::RenderBorderColor,
    Api::RenderTextColor
>;

struct RenderDefinition
{
    std::vector<Api::RenderOp> ops;

    auto empty() const -> bool
    {
        return ops.empty();
    }
};

struct RenderStates
{
    Api::RenderDefinition normal;
    Api::RenderDefinition hover;
    Api::RenderDefinition focus;
    Api::RenderDefinition pressed;
    Api::RenderDefinition disabled;
    Api::RenderDefinition dragOver;

    auto empty() const -> bool
    {
        return normal.empty()
            && hover.empty()
            && focus.empty()
            && pressed.empty()
            && disabled.empty()
            && dragOver.empty();
    }

    auto forState(Api::WidgetState state) const -> const Api::RenderDefinition&
    {
        switch (state)
        {
        case Api::WidgetState::Hover:
            return hover.empty() ? normal : hover;

        case Api::WidgetState::Focus:
            return focus.empty() ? normal : focus;

        case Api::WidgetState::Pressed:
            return pressed.empty() ? normal : pressed;

        case Api::WidgetState::Disabled:
            return disabled.empty() ? normal : disabled;

        case Api::WidgetState::DragOver:
            return dragOver.empty() ? normal : dragOver;

        case Api::WidgetState::Normal:
        default:
            return normal;
        }
    }
};

} // namespace Blade::Api

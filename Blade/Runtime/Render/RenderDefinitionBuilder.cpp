#include "RenderDefinitionBuilder.h"

#include <type_traits>

namespace Blade {

auto RenderDefinitionBuilder::Build(const Api::Modifier& modifier) -> Api::RenderStates
{
    return {
        .normal = buildForState(modifier, Api::WidgetState::Normal),
        .hover = buildForState(modifier, Api::WidgetState::Hover),
        .focus = buildForState(modifier, Api::WidgetState::Focus),
        .pressed = buildForState(modifier, Api::WidgetState::Pressed),
        .disabled = buildForState(modifier, Api::WidgetState::Disabled),
        .dragOver = buildForState(modifier, Api::WidgetState::DragOver),
    };
}

auto RenderDefinitionBuilder::buildForState(const Api::Modifier& modifier, Api::WidgetState state) -> Api::RenderDefinition
{
    Api::RenderDefinition definition;
    append(modifier, state, definition);
    return definition;
}

auto RenderDefinitionBuilder::append(const Api::Modifier& modifier, Api::WidgetState state, Api::RenderDefinition& out) -> void
{
    for (const auto& op : modifier.ops())
    {
        append(op, state, out);
    }
}

auto RenderDefinitionBuilder::append(const Api::ModifierOp& op, Api::WidgetState state, Api::RenderDefinition& out) -> void
{
    std::visit(
        [state, &out](const auto& modifier)
        {
            using T = std::decay_t<decltype(modifier)>;

            if constexpr (std::is_same_v<T, Api::BackgroundModifier>)
            {
                out.ops.push_back(Api::RenderBackground{modifier.value});
            }
            else if constexpr (std::is_same_v<T, Api::BorderRadiusModifier>)
            {
                out.ops.push_back(Api::RenderBorderRadius{modifier.value});
            }
            else if constexpr (std::is_same_v<T, Api::BorderColorModifier>)
            {
                out.ops.push_back(Api::RenderBorderColor{modifier.value});
            }
            else if constexpr (std::is_same_v<T, Api::TextColorModifier>)
            {
                out.ops.push_back(Api::RenderTextColor{modifier.value});
            }
            else if constexpr (std::is_same_v<T, Api::StateModifiers>)
            {
                appendState(modifier, state, out);
            }
        },
        op
    );
}

auto RenderDefinitionBuilder::appendState(const Api::StateModifiers& states, Api::WidgetState state, Api::RenderDefinition& out) -> void
{
    const auto* modifier = branch(states, state);
    if (!modifier) modifier = states.normal.get();
    if (modifier) append(*modifier, state, out);
}

auto RenderDefinitionBuilder::branch(const Api::StateModifiers& states, Api::WidgetState state) -> const Api::Modifier*
{
    switch (state)
    {
    case Api::WidgetState::Hover:
        return states.hover.get();

    case Api::WidgetState::Focus:
        return states.focus.get();

    case Api::WidgetState::Pressed:
        return states.pressed.get();

    case Api::WidgetState::Disabled:
        return states.disabled.get();

    case Api::WidgetState::DragOver:
        return states.dragOver.get();

    case Api::WidgetState::Normal:
    default:
        return states.normal.get();
    }
}

} // namespace Blade

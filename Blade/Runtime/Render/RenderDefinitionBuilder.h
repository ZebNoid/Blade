#pragma once

#include "Common/Modifier.h"
#include "Render/RenderOp.h"

namespace Blade {

class RenderDefinitionBuilder
{
public:
    static auto Build(const Api::Modifier& modifier) -> Api::RenderStates;

private:
    static auto buildForState(const Api::Modifier& modifier, Api::WidgetState state) -> Api::RenderDefinition;
    static auto append(const Api::Modifier& modifier, Api::WidgetState state, Api::RenderDefinition& out) -> void;
    static auto append(const Api::ModifierOp& op, Api::WidgetState state, Api::RenderDefinition& out) -> void;
    static auto appendState(const Api::StateModifiers& states, Api::WidgetState state, Api::RenderDefinition& out) -> void;
    static auto branch(const Api::StateModifiers& states, Api::WidgetState state) -> const Api::Modifier*;
};

} // namespace Blade

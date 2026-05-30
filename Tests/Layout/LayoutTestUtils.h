#pragma once

#include "Runtime/LayoutRuntime/LayoutPass/LayoutPass.h"
#include "Runtime/ModifierTree/ModifierTreeBuilder.h"

namespace Blade::Tests {

inline auto BuildLayout(WidgetTree tree, Api::Size available) -> LayoutNode
{
    return Layout::Pass::Compute(ModifierTree::Builder::Expand(std::move(tree)), available);
}

} // namespace Blade::Tests

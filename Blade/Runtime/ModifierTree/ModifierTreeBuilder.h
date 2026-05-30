#pragma once

#include "Base/WidgetTree.h"

namespace Blade {

class ModifierTreeBuilder
{
public:
    static auto Expand(WidgetTree tree) -> WidgetTree;

private:
    static auto expandChildren(WidgetTree& tree) -> void;
    static auto expandNode(WidgetTree node) -> WidgetTree;
    static auto wrap(WidgetTree node, const Api::ModifierOp& op) -> WidgetTree;
};

} // namespace Blade

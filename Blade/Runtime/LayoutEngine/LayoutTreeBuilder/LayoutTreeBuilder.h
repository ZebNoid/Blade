#pragma once
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"

namespace Blade {


class LayoutTreeBuilder
{
public:
    static auto Build(
        const WidgetTree& tree
    ) -> LayoutNode;

private:
    static auto BuildNode(
        const WidgetTree& tree
    ) -> LayoutNode;
};


} // namespace

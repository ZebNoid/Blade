#pragma once

#include "Runtime/LayoutEngine/LayoutNode.h"


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

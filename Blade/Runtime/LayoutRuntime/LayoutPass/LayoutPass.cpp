#include "LayoutPass.h"

#include "Runtime/LayoutEngine/Data/LayoutContext.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"
#include "Runtime/LayoutEngine/LayoutTreeBuilder/LayoutTreeBuilder.h"


namespace Blade {

auto LayoutPass::Build(const WidgetTree& tree, const Api::Size& available) -> LayoutNode
{
    auto layoutTree = LayoutTreeBuilder::Build(tree);
    layoutTree.layout.size = available;

    LayoutContext measureCtx{ .node = &layoutTree, .available = available };
    LayoutEngine::Measure(measureCtx);

    LayoutContext arrangeCtx{
        .node = &layoutTree,
        .rect = { 0, 0, available.width, available.height }
    };

    LayoutEngine::Arrange(arrangeCtx);

    return layoutTree;
}

} // namespace Blade

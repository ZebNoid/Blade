#include "LayoutTreeBuilder.h"


namespace Blade {


auto LayoutTreeBuilder::Build(
    const WidgetTree& tree
) -> LayoutNode
{
    return BuildNode(tree);
}

auto LayoutTreeBuilder::BuildNode(
    const WidgetTree& tree
) -> LayoutNode
{
    LayoutNode node;

    node.id = tree.id;

    node.type = tree.type;

    node.layout = tree.layout;

    // -------------------------------------------------
    // Layout type
    // -------------------------------------------------

    node.layoutType = tree.layoutType;

    node.isNative = node.layoutType == LayoutType::None;

    for (const auto& child : tree.children)
    {
        node.children.push_back(
            BuildNode(child)
        );
    }

    return node;
}


} // namespace

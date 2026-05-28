#include "LayoutTreeBuilder.h"


namespace Blade {


auto LayoutTreeBuilder::Build(const WidgetTree& tree) -> LayoutNode
{
    return BuildNode(tree);
}

auto LayoutTreeBuilder::BuildNode(const WidgetTree& tree) -> LayoutNode
{
    LayoutNode node;

    node.id = tree.id;
    node.type = tree.type;
    node.layout = tree.layout;
    node.layoutType = tree.layoutType;

    for (const auto& child : tree.children)
    {
        node.children.push_back(BuildNode(child));
    }

    if (node.layoutType == LayoutType::Virtual && node.children.size() == 1)
    {
        node.layout = node.children.front().layout;
    }

    return node;
}


} // namespace

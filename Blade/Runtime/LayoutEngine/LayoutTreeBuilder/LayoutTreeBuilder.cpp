#include "LayoutTreeBuilder.h"


namespace Blade::Layout::TreeBuilder {

namespace {

auto InheritParentLayoutHints(LayoutNode& node) -> void
{
    if (node.layoutType != LayoutType::Virtual || node.children.size() != 1) return;

    const auto& child = node.children.front();
    node.layout.box.flex = child.layout.box.flex;
    node.layout.size = child.layout.size;
}

auto BuildNode(const WidgetTree& tree) -> LayoutNode
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

    InheritParentLayoutHints(node);

    return node;
}

} // namespace

auto Build(const WidgetTree& tree) -> LayoutNode
{
    return BuildNode(tree);
}

} // namespace Blade::Layout::TreeBuilder

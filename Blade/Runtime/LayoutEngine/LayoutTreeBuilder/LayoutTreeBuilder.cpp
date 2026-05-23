#include "LayoutTreeBuilder.h"

#include <unordered_map>


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

    // temporary heuristic
    node.isNative =
        tree.type != L"Column" &&
        tree.type != L"Row" &&
        tree.type != L"Stack";

    // extract layout props
    // tree.layout[] // TODO
    // if (const auto it = tree.props.find(Api::Props::Layout); // props separate for blade? not for backend
    //     it != tree.props.end())
    // {
    //     try
    //     {
    //         node.layout =
    //             std::any_cast<Api::LayoutProps>(
    //                 tree.props
    //             );
    //     }
    //     catch (...)
    //     {
    //     }
    // }

    for (const auto& child : tree.children)
    {
        node.children.push_back(
            BuildNode(child)
        );
    }

    return node;
}

} // namespace

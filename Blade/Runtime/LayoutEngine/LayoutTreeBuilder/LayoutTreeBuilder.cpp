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

    node.layout = ExtractLayoutData(tree.props);

    node.isNative = IsNativeWidget(tree.type);

    for (const auto& child : tree.children)
    {
        node.children.push_back(
            BuildNode(child)
        );
    }

    return node;
}


auto LayoutTreeBuilder::ExtractLayoutData(
    const Api::PropertyMap& props
) -> LayoutData
{
    LayoutData data;

    // LayoutProps
    if (const auto it =
            props.find(Api::Props::Layout);
        it != props.end())
    {
        if (const auto* layout =
            std::get_if<Api::LayoutProps>(
                &it->second
            ))
        {
            data.layout = *layout;
        }
    }

    // Gap
    if (const auto it =
            props.find(Api::Props::Gap);
        it != props.end())
    {
        if (const auto* gap =
            std::get_if<int>(
                &it->second
            ))
        {
            data.gap = *gap;
        }
    }

    return data;
}

auto LayoutTreeBuilder::IsNativeWidget(
    const Api::Text& type
) -> bool
{
    return
        type != L"Column" &&
        type != L"Row" &&
        type != L"Stack";
}


} // namespace

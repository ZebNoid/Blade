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

    // Size
    if (const auto it =
            props.find(Api::Props::Size);
        it != props.end())
    {
        if (const auto* size =
            std::get_if<Api::Size>(
                &it->second
            ))
        {
            data.size = *size;
        }
    }

    // Position
    if (const auto it =
            props.find(Api::Props::Position);
        it != props.end())
    {
        if (const auto* position =
            std::get_if<Api::Point>(
                &it->second
            ))
        {
            data.position = *position;
        }
    }

    return data;
}


} // namespace

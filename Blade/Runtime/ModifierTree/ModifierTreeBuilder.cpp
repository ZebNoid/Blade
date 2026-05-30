#include "ModifierTreeBuilder.h"

#include <type_traits>

namespace Blade::ModifierTree::Builder {

namespace {

auto VirtualWrapper(Api::WidgetType type, WidgetTree child) -> WidgetTree
{
    WidgetTree wrapper;
    wrapper.type = std::move(type);
    wrapper.layoutType = LayoutType::Virtual;
    wrapper.children.push_back(std::move(child));
    return wrapper;
}

auto StateBranch(const Api::StateModifiers& states, WidgetTree child) -> WidgetTree
{
    auto wrapper = VirtualWrapper(Api::WidgetTypes::ModifierStates, std::move(child));
    wrapper.modifier.states(states);
    return wrapper;
}

auto Wrap(WidgetTree node, const Api::ModifierOp& op) -> WidgetTree
{
    return std::visit(
        [&node](const auto& modifier) mutable -> WidgetTree
        {
            using T = std::decay_t<decltype(modifier)>;

            if constexpr (std::is_same_v<T, Api::PaddingModifier>)
            {
                auto wrapper = VirtualWrapper(Api::WidgetTypes::ModifierPadding, std::move(node));
                wrapper.layout.box.padding = modifier.value;
                return wrapper;
            }
            else if constexpr (std::is_same_v<T, Api::BackgroundModifier>)
            {
                return VirtualWrapper(Api::WidgetTypes::ModifierBackground, std::move(node));
            }
            else if constexpr (std::is_same_v<T, Api::StateModifiers>)
            {
                return StateBranch(modifier, std::move(node));
            }
            else
            {
                return std::move(node);
            }
        },
        op
    );
}

auto ExpandNode(WidgetTree node) -> WidgetTree;

auto ExpandChildren(WidgetTree& tree) -> void
{
    for (auto& child : tree.children)
    {
        child = ExpandNode(std::move(child));
    }

    for (auto& overlay : tree.overlays)
    {
        overlay = ExpandNode(std::move(overlay));
    }
}

auto ExpandNode(WidgetTree node) -> WidgetTree
{
    ExpandChildren(node);

    auto result = std::move(node);
    const auto ops = result.modifier.ops();
    for (const auto& op : ops)
    {
        result = Wrap(std::move(result), op);
    }

    return result;
}

} // namespace

auto Expand(WidgetTree tree) -> WidgetTree
{
    if (tree.layoutType != LayoutType::None)
    {
        return ExpandNode(std::move(tree));
    }

    ExpandChildren(tree);
    return tree;
}

} // namespace Blade::ModifierTree::Builder

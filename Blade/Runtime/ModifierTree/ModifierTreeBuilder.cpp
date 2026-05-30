#include "ModifierTreeBuilder.h"

#include <type_traits>

namespace Blade {

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

} // namespace

auto ModifierTreeBuilder::Expand(WidgetTree tree) -> WidgetTree
{
    expandChildren(tree);
    return tree;
}

auto ModifierTreeBuilder::expandChildren(WidgetTree& tree) -> void
{
    for (auto& child : tree.children)
    {
        child = expandNode(std::move(child));
    }

    for (auto& overlay : tree.overlays)
    {
        overlay = expandNode(std::move(overlay));
    }
}

auto ModifierTreeBuilder::expandNode(WidgetTree node) -> WidgetTree
{
    expandChildren(node);

    auto result = std::move(node);
    const auto ops = result.modifier.ops();
    for (const auto& op : ops)
    {
        result = wrap(std::move(result), op);
    }

    return result;
}

auto ModifierTreeBuilder::wrap(WidgetTree node, const Api::ModifierOp& op) -> WidgetTree
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

} // namespace Blade

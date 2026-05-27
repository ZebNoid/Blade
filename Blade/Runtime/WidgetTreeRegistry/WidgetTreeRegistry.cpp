#include "WidgetTreeRegistry.h"


namespace Blade {

auto WidgetTreeRegistry::add(WidgetTree tree) -> WidgetTree&
{
    assignIds(tree);
    const auto rootId = tree.id;
    auto [it, inserted] = m_roots.insert_or_assign(rootId, std::move(tree));
    return it->second;
}

auto WidgetTreeRegistry::root(Api::Id rootId) -> WidgetTree*
{
    const auto it = m_roots.find(rootId);
    return it == m_roots.end() ? nullptr : &it->second;
}

auto WidgetTreeRegistry::find(Api::Id widgetId) -> WidgetTree*
{
    for (auto& [rootId, tree] : m_roots)
    {
        if (auto* widget = findIn(tree, widgetId))
        {
            return widget;
        }
    }

    return nullptr;
}

auto WidgetTreeRegistry::assignIds(WidgetTree& tree) -> void
{
    assignNodeIds(tree);
}

auto WidgetTreeRegistry::assignNodeIds(WidgetTree& node) -> void
{
    if (node.id == Api::InvalidId)
    {
        node.id = nextId();
    }

    for (auto& child : node.children)
    {
        assignNodeIds(child);
    }
}

auto WidgetTreeRegistry::findIn(WidgetTree& node, Api::Id widgetId) -> WidgetTree*
{
    if (node.id == widgetId)
    {
        return &node;
    }

    for (auto& child : node.children)
    {
        if (auto* widget = findIn(child, widgetId))
        {
            return widget;
        }
    }

    return nullptr;
}

auto WidgetTreeRegistry::nextId() -> Api::Id
{
    return m_nextId++;
}

} // namespace Blade

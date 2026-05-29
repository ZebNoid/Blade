#include "WidgetTreeRegistry.h"

#include "Common/Lifetime.h"


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

auto WidgetTreeRegistry::rootIds() const -> std::vector<Api::Id>
{
    std::vector<Api::Id> ids;
    ids.reserve(m_roots.size());

    for (const auto& [rootId, _] : m_roots)
    {
        ids.push_back(rootId);
    }

    return ids;
}

auto WidgetTreeRegistry::remove(Api::Id rootId) -> void
{
    m_roots.erase(rootId);
}

auto WidgetTreeRegistry::clear() -> void
{
    m_roots.clear();
}

auto WidgetTreeRegistry::ownerCount() const -> size_t
{
    size_t count = 0;

    for (const auto& [rootId, tree] : m_roots)
    {
        const auto it = tree.backend.create.find(Api::Props::Lifetime);
        const auto* lifetime = it == tree.backend.create.end() ? nullptr : std::get_if<Api::Lifetime>(&it->second);

        if (!lifetime || *lifetime == Api::Lifetime::Owner)
        {
            ++count;
        }
    }

    return count;
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

    for (auto& overlay : node.overlays)
    {
        assignNodeIds(overlay);
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

    for (auto& overlay : node.overlays)
    {
        if (auto* widget = findIn(overlay, widgetId))
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

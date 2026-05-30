#include "NodeRegistry.h"


namespace Blade::Backend {


auto NodeRegistry::add(NativeNode node) -> void
{
    node.order = m_nextOrder++;

    // m_nodes[node.id] = std::move(node);
    m_nodes.emplace(
        node.id,
        std::move(node)
    );
}

auto NodeRegistry::get(Api::Id id) -> NativeNode*
{
    auto it = m_nodes.find(id);

    if (it == m_nodes.end())
    {
        return nullptr;
    }

    return &it->second;
}

auto NodeRegistry::remove(Api::Id id) -> void
{
    m_nodes.erase(id);
}

auto NodeRegistry::clear() -> void
{
    m_nodes.clear();
}

auto NodeRegistry::count() const -> size_t
{
    return m_nodes.size();
}

auto NodeRegistry::forEach(const std::function<void(NativeNode&)>& callback) -> void
{
    for (auto& [_, node] : m_nodes)
    {
        callback(node);
    }
}

} // namespace

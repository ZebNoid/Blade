#include "NodeRegistry.h"


namespace Blade::Backend {


auto NodeRegistry::add(NativeNode node) -> void
{
    m_nodes[node.id] = std::move(node);
}

auto NodeRegistry::remove(Api::Id id) -> void
{
    m_nodes.erase(id);
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


} // namespace

#include "NodeRegistry.h"


namespace Blade::Backend {


auto NodeRegistry::add(NativeNode node) -> void
{
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

auto NodeRegistry::collectGarbage() -> void
{
    // TODO where to use?
    std::erase_if(
        m_nodes,
        [](const auto& pair)
        {
            const auto& node = pair.second;

            if (!node.native)
            {
                return true;
            }

            return !node.native->isAlive();
        }
    );
}


} // namespace

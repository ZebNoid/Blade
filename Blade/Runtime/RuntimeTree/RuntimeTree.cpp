#include "RuntimeTree.h"


namespace Blade {

auto RuntimeTree::assignIds(WidgetTree& tree) -> void
{
    assignNodeIds(tree);
}

auto RuntimeTree::assignNodeIds(WidgetTree& node) -> void
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

auto RuntimeTree::nextId() -> Api::Id
{
    return m_nextId++;
}

} // namespace Blade

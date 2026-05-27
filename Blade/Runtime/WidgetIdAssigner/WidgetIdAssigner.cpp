#include "WidgetIdAssigner.h"


namespace Blade {

auto WidgetIdAssigner::assignIds(WidgetTree& tree) -> void
{
    assignNodeIds(tree);
}

auto WidgetIdAssigner::assignNodeIds(WidgetTree& node) -> void
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

auto WidgetIdAssigner::nextId() -> Api::Id
{
    return m_nextId++;
}

} // namespace Blade

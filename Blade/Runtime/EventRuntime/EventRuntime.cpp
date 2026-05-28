#include "EventRuntime.h"

#include "EventInvoker.h"


namespace Blade {

auto EventRuntime::registerTree(const WidgetTree& tree) -> void
{
    if (!tree.events.empty())
    {
        m_events.insert_or_assign(tree.id, tree.events);
    }

    for (const auto& child : tree.children)
    {
        registerTree(child);
    }

    for (const auto& overlay : tree.overlays)
    {
        registerTree(overlay);
    }
}

auto EventRuntime::dispatch(const Api::BackendEvent& event) -> Api::EventResult
{
    const auto nodeIt = m_events.find(event.target);

    if (nodeIt == m_events.end())
    {
        return {};
    }

    const auto eventIt = nodeIt->second.find(event.type);

    if (eventIt == nodeIt->second.end())
    {
        return {};
    }

    return InvokeEvent(eventIt->second, event);
}

} // namespace Blade

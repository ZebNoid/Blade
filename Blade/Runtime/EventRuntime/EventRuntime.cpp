#include "EventRuntime.h"


namespace Blade {

auto EventRuntime::registerTree(
    const WidgetTree& tree
) -> void
{
    if (!tree.events.empty())
    {
        m_events.insert_or_assign(
            tree.id,
            tree.events
        );
    }

    for (const auto& child : tree.children)
    {
        registerTree(child);
    }
}

auto EventRuntime::dispatch(
    const Api::BackendEvent& event
) -> Api::EventResult
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

    if (const auto* callback = std::get_if<Api::CallbackVoid>(&eventIt->second))
    {
        if (*callback)
        {
            (*callback)();
        }
    }

    return {};
}

} // namespace Blade

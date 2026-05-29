#include "EventRuntime.h"

#include "EventInvoker.h"


namespace Blade {

auto EventRuntime::registerTree(const WidgetTree& tree) -> void
{
    registerTree(tree, Api::InvalidId);
}

auto EventRuntime::registerTree(const WidgetTree& tree, Api::Id parent) -> void
{
    if (!tree.events.empty())
    {
        m_events.insert_or_assign(tree.id, tree.events);
    }

    if (parent != Api::InvalidId)
    {
        m_parents.insert_or_assign(tree.id, parent);
    }

    for (const auto& child : tree.children)
    {
        registerTree(child, tree.id);
    }

    for (const auto& overlay : tree.overlays)
    {
        registerTree(overlay, tree.id);
    }
}

auto EventRuntime::dispatch(const Api::BackendEvent& event) -> Api::EventResult
{
    Api::EventResult result;
    Api::EventContext context{
        .target = event.target,
        .type = event.type,
        .payload = &event.payload
    };

    for (auto target = event.target; target != Api::InvalidId; target = parentOf(target))
    {
        if (hasHandler(target, event.type))
        {
            context.currentTarget = target;
            result = dispatchNode(target, event, context);
            if (context.propagationStopped) return result;
        }
    }

    return result;
}

auto EventRuntime::hasHandler(Api::Id target, Api::Events event) const -> bool
{
    const auto nodeIt = m_events.find(target);
    return nodeIt != m_events.end() && nodeIt->second.contains(event);
}

auto EventRuntime::dispatchNode(Api::Id target, const Api::BackendEvent& event, Api::EventContext& context) -> Api::EventResult
{
    const auto nodeIt = m_events.find(target);

    if (nodeIt == m_events.end()) return {};

    const auto eventIt = nodeIt->second.find(event.type);

    if (eventIt == nodeIt->second.end()) return {};

    return InvokeEvent(eventIt->second, event, context);
}

auto EventRuntime::parentOf(Api::Id target) const -> Api::Id
{
    const auto it = m_parents.find(target);
    return it == m_parents.end() ? Api::InvalidId : it->second;
}

} // namespace Blade

#pragma once

#include <unordered_map>

#include "../../Core/Core.h"
#include "../../Events/WidgetEvent/WidgetEvent.h"
#include "../../Events/WidgetEvent/EventKey.h"

class EventRouter
{
public:
    auto AllocateId() -> WidgetId
    {
        return m_nextId++;
    }

    auto BindEvent(
        const WidgetId id,
        const WidgetEvent event,
        EventHandler fn
    ) -> void
    {
        m_events[{id, event}] = std::move(fn);
    }

    auto DispatchCommand(
        const WidgetId id,
        const WidgetEvent event,
        const EventValue& value = {}
    ) -> void
    {
        const auto it = m_events.find({id, event});
        if (it == m_events.end()) return;
        if (it->second == nullptr) return;
        it->second(value);
    }

private:
    WidgetId m_nextId = 1;

    std::unordered_map<
        EventKey,
        EventHandler,
        EventKeyHash
    > m_events;
};

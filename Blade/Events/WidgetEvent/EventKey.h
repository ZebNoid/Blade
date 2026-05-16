#pragma once

#include <functional>

#include "../../Core/Core.h"
#include "WidgetEvent.h"

struct EventKey
{
    WidgetId id;
    WidgetEvent event;

    auto operator==(const EventKey&) const -> bool = default;
};

struct EventKeyHash
{
    auto operator()(const EventKey& k) const -> size_t
    {
        return
            std::hash<int>()(k.id)
            ^
            (std::hash<int>()((int)k.event) << 1);
    }
};
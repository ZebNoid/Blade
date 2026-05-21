#pragma once

#include <functional>

#include "Core/Core.h"
#include "Events/WidgetEvent/WidgetEvent.h"


namespace Blade {


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


} // namespace

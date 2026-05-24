#include "EventSubscriptions.h"


namespace Blade {

auto ToEventSubscriptions(const Api::EventMap& events) -> Api::EventSubscriptions
{
    Api::EventSubscriptions subscriptions;

    for (const auto& [event, _] : events)
    {
        subscriptions.push_back(event);
    }

    return subscriptions;
}

} // namespace Blade

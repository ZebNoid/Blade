#pragma once

#include <utility>


namespace Blade {


template <typename Derived>
class EventMixin
{
public:
    template <typename Event, typename Handler>
    auto on(Event, Handler handler) -> Derived&
    {
        static_cast<Derived*>(this)->addHandler(Event{}, std::move(handler));
        return static_cast<Derived&>(*this);
    }
};


} // namespace

#pragma once


#include "Common/Events.h"
#include "Common/Property.h"


namespace Blade {


class EventVisitor
{
public:
    auto set(const Api::Events& key, const Api::EventsValue& value) -> void
    {
        if (key == Api::Events::Unknown || IsEmpty(value))
        {
            return;
        }

        m_map[key] = value;
    }

    auto take() const -> const Api::EventMap&
    {
        return m_map;
    }

private:
    static auto IsEmpty(const Api::EventsValue& value) -> bool
    {
        return std::visit(
            [](const auto& callback)
            {
                return !callback;
            },
            value
        );
    }

private:
    Api::EventMap m_map;
};


} // namespace

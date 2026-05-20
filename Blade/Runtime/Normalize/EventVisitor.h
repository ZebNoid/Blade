#pragma once


#include "Common/Types.h"
#include "Common/Property.h"


namespace Blade {


class EventVisitor
{
public:
    auto set(const Api::Text& key, const Api::EventsValue& value) -> void
    {
        m_map[key] = value;
    }

    auto map() const -> const Api::EventMap&
    {
        return m_map;
    }

private:
    Api::EventMap m_map;
};


} // namespace

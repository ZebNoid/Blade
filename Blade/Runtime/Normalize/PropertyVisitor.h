#pragma once

#include "Common/Property.h"


namespace Blade {

class PropertyVisitor
{
public:
    auto set(const Api::Props& prop, const Api::PropertyValue& value) -> void
    {
        m_map[prop] = value;
    }

    auto take() const -> const Api::PropertyMap&
    {
        return m_map;
    }

private:
    Api::PropertyMap m_map;
};

} // namespace

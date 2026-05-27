#pragma once

#include "Common/Property.h"

namespace Blade::Backend {

class PropertyReader
{
public:
    template <typename T>
    static auto Get(const Api::PropertyMap& propertyMap, Api::Props prop) -> const T*
    {
        const auto it = propertyMap.find(prop);
        return it == propertyMap.end() ? nullptr : std::get_if<T>(&it->second);
    }
};

} // namespace Blade::Backend

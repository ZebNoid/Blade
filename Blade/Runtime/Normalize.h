#pragma once

#include "Common/Types.h"
#include "Common/Property.h"


namespace Blade {


class Normalize
{
public:
    template <typename T>
    static auto Props(const T& src) -> Api::PropertyMap
    {
        Api::PropertyMap map;

        src.visit(
            [&](const Api::Text& key, const Api::PropertyValue& value)
            {
                map[key] = value;
            }
        );

        return map;
    }

    template <typename T>
    static auto Events(const T& src) -> EventMap
    {
        EventMap map;

        src.visit(
            [&](const Api::Text& name, auto&& value)
            {
                if (value)
                {
                    map[name] = value;
                }
            }
        );

        return map;
    }
};

} // namespace

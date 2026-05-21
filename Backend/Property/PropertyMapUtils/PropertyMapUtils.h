#pragma once

#include "Common/Property.h"

namespace Blade::Backend {


class PropertyMapUtils
{
public:
    template <typename T>
    static auto get(
        const Api::PropertyMap& props,
        const Api::Props& key
    ) -> const T*
    {
        auto it = props.find(key);

        if (it == props.end())
        {
            return nullptr;
        }

        return std::get_if<T>(&it->second);
    }
};


} // namespace

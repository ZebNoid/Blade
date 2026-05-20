#pragma once

#include "Common/Types.h"
#include "Common/Property.h"


namespace Blade {

// class PropertyVisitor
// {
// public:
//     virtual ~PropertyVisitor() = default;
//
//     virtual auto set(
//         const Api::Text& key,
//         const Api::PropertyValue& value
//     ) -> void = 0;
// };

class PropertyVisitor
{
public:
    // explicit PropertyVisitor(Api::PropertyMap& map)
    //     : m_map(map)
    // {
    // }

    auto set(const Api::Text& key, const Api::PropertyValue& value) -> void
    {
        m_map[key] = value;
    }

    auto map() const -> const Api::PropertyMap&
    {
        return m_map;
    }

private:
    Api::PropertyMap m_map;
};

} // namespace

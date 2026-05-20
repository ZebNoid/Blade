#pragma once

#include "Common/Types.h"
#include "Common/Property.h"

namespace Blade {

class PropertyVisitor
{
public:
    virtual ~PropertyVisitor() = default;

    virtual auto set(
        const Api::Text& key,
        const Api::PropertyValue& value
    ) -> void = 0;
};

} // namespace
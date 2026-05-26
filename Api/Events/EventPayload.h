#pragma once

#include <variant>

#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade::Api {

using EventPayload = std::variant<
    std::monostate,
    bool,
    int,
    Api::Text,
    Api::Size
>;

} // namespace Blade::Api

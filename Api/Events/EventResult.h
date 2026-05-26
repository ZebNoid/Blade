#pragma once

#include <variant>

#include "Common/Types.h"


namespace Blade::Api {

using EventResult = std::variant<
    std::monostate,
    bool,
    int,
    Api::Text
>;

} // namespace Blade::Api

#pragma once

#include <variant>

#include "Command/AppCommandType.h"
#include "Common/Types.h"

namespace Blade::Api {

struct AppCommand
{
    Api::AppCommandType command;
    Api::Id target = Api::InvalidId;
    std::variant<std::monostate, Api::Text> payload;
};

} // namespace Blade::Api

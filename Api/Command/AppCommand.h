#pragma once

#include "Command/AppCommandType.h"
#include "Common/Types.h"

namespace Blade::Api {

struct AppCommand
{
    Api::AppCommandType command;
    Api::Id target = Api::InvalidId;
};

} // namespace Blade::Api

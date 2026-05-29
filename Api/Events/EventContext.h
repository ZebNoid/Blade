#pragma once

#include "Common/Types.h"
#include "Events.h"
#include "EventPayload.h"

namespace Blade::Api {

struct EventContext
{
    Api::Id target = Api::InvalidId;
    Api::Id currentTarget = Api::InvalidId;
    Api::Events type = Api::Events::Unknown;
    const Api::EventPayload* payload = nullptr;
};

} // namespace Blade::Api

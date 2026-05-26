#pragma once

#include "EventPayload.h"
#include "Events.h"


namespace Blade::Api {

struct BackendEvent
{
    Api::Id target = Api::InvalidId;
    Api::Events type = Api::Events::Unknown;
    Api::EventPayload payload{};
};

} // namespace Blade::Api

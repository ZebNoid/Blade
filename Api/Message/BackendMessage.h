#pragma once

#include <variant>

#include "Geometry/Size.h"
#include "Events/BackendEvent.h"
#include "Events/EventResult.h"
#include "Message/BackendMessageType.h"


namespace Blade::Api {

struct BackendResize
{
    Api::Id target = Api::InvalidId;
    Api::Size size{};
};

struct BackendDestroyed
{
    Api::Id target = Api::InvalidId;
};

using BackendMessagePayload = std::variant<
    std::monostate,
    Api::BackendResize,
    Api::BackendEvent,
    Api::BackendDestroyed
>;

struct BackendMessage
{
    Api::BackendMessageType type = Api::BackendMessageType::Unknown;
    Api::BackendMessagePayload payload{};
};

using BackendMessageHandler = std::function<Api::EventResult(const Api::BackendMessage&)>;

} // namespace Blade::Api

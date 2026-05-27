#pragma once

#include "Command/ElementCommand.h"
#include "Message/BackendMessage.h"


namespace Blade::Api {

class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto init() -> void = 0;

    virtual auto runApp() -> int = 0;

    virtual auto quit() -> void = 0;

    virtual auto setMessageHandler(
        BackendMessageHandler handler
    ) -> void = 0;

    virtual auto process(
        const Api::ElementCommand& command
    ) -> void = 0;
};


}

#pragma once
#include <functional>

#include "BackendCommand.h"
#include "Common/Events.h"
#include "Common/Size.h"


namespace Blade::Api {

using ResizeHandler = std::function<void(Api::Id, const Api::Size&)>;
using EventHandler = std::function<EventResult(const BackendEvent&)>;


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto init() -> void = 0;

    virtual auto runApp() -> int = 0;

    virtual auto quit() -> void = 0;

    virtual auto setResizeHandler(
        ResizeHandler handler
    ) -> void = 0;

    virtual auto setEventHandler(
        EventHandler handler
    ) -> void = 0;

    virtual auto process(
        const Api::BackendCommand& command
    ) -> void = 0;
};


}

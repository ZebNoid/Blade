#pragma once
#include <functional>
#include <variant>

#include "BackendCommand.h"
#include "Common/Events.h"
#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade::Api {

using ResizeHandler = std::function<void(Api::Id, const Api::Size&)>;

using EventResult = std::variant<
    std::monostate,
    bool,
    int,
    Api::Text
>;

struct BackendEvent
{
    Api::Id target = Api::InvalidId;
    Api::Events type = Api::Events::Unknown;
};

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

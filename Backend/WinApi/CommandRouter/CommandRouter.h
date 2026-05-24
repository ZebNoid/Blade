#pragma once

#include "Api/ApiBackend.h"
#include "Common/Property.h"
#include "Common/Types.h"


namespace Blade::Backend {

class CommandRouter
{
public:
    explicit CommandRouter(
        Api::EventHandler* handler = nullptr
    );

    auto setHandler(
        Api::EventHandler* handler
    ) -> void;

    auto on(
        Api::Id id,
        Api::Events event
    ) -> void;

    auto dispatch(
        WPARAM wParam,
        LPARAM lParam
    ) -> bool;

private:
    Api::EventHandler* m_handler = nullptr;
    std::unordered_map<Api::Id, Api::Events> m_handlers;
};

} // namespace Blade::Backend

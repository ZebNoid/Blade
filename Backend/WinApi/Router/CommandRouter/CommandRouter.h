#pragma once

#include <unordered_map>
#include <vector>
#include <windows.h>

#include "Api/ApiBackend.h"


namespace Blade::Backend {

class CommandRouter
{
public:
    explicit CommandRouter(Api::EventHandler* handler = nullptr);

    auto setHandler(Api::EventHandler* handler) -> void;

    auto on(Api::Id id, Api::Events event) -> void;

    auto dispatch(WPARAM wParam, LPARAM lParam) -> bool;

private:
    Api::EventHandler* m_handler = nullptr;
    std::unordered_map<Api::Id, std::vector<Api::Events>> m_subscriptions;
};

} // namespace Blade::Backend

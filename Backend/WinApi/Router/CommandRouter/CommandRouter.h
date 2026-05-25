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

    auto on(Api::Id id, WORD notificationCode, Api::BackendEvent event) -> void;

    auto emit(Api::BackendEvent event) -> bool;

    auto dispatch(WPARAM wParam, LPARAM lParam) -> bool;

private:
    struct Subscription
    {
        WORD notificationCode = 0;
        Api::BackendEvent event{};
    };

    static auto findSubscription(
        std::vector<Subscription>& subscriptions,
        WORD notificationCode
    ) -> Subscription*;

private:
    Api::EventHandler* m_handler = nullptr;
    std::unordered_map<Api::Id, std::vector<Subscription>> m_subscriptions;
};

} // namespace Blade::Backend

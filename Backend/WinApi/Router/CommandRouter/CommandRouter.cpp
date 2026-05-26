#include "CommandRouter.h"

#include <algorithm>


namespace Blade::Backend {

auto CommandRouter::findSubscription(
    std::vector<Subscription>& subscriptions,
    WORD notificationCode
) -> Subscription*
{
    const auto it = std::ranges::find_if(
        subscriptions,
        [notificationCode](const auto& subscription)
        {
            return subscription.notificationCode == notificationCode;
        }
    );

    if (it == subscriptions.end())
    {
        return nullptr;
    }

    return &*it;
}

CommandRouter::CommandRouter(Api::EventHandler* handler)
    : m_handler(handler)
{
}

auto CommandRouter::setHandler(Api::EventHandler* handler) -> void
{
    m_handler = handler;
}

auto CommandRouter::on(Api::Id id, WORD notificationCode, Api::BackendEvent event) -> void
{
    if (id == Api::InvalidId || event.type == Api::Events::Unknown)
    {
        return;
    }

    auto& subscriptions = m_subscriptions[id];
    auto* subscription = findSubscription(subscriptions, notificationCode);

    if (subscription)
    {
        subscription->event = std::move(event);
        return;
    }

    subscriptions.push_back({
        .notificationCode = notificationCode,
        .event = std::move(event)
    });
}

auto CommandRouter::emit(Api::BackendEvent event) -> bool
{
    if (event.type == Api::Events::Unknown)
    {
        return false;
    }

    if (!m_handler || !*m_handler)
    {
        return false;
    }

    (*m_handler)(event);

    return true;
}

auto CommandRouter::dispatch(WPARAM wParam, LPARAM lParam) -> bool
{
    if (!lParam)
    {
        return false;
    }

    const auto id = static_cast<Api::Id>(LOWORD(wParam));
    const auto notificationCode = HIWORD(wParam);

    const auto it = m_subscriptions.find(id);

    if (it == m_subscriptions.end())
    {
        return false;
    }

    auto* subscription = findSubscription(it->second, notificationCode);

    if (!subscription)
    {
        return false;
    }

    if (!m_handler || !*m_handler)
    {
        return false;
    }

    auto event = subscription->event;
    event.target = id;
    return emit(event);
}

} // namespace Blade::Backend

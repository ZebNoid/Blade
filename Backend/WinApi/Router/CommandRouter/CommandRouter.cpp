#include "CommandRouter.h"

#include <algorithm>


namespace Blade::Backend {

namespace {

auto ToCommandEvent(WORD notificationCode) -> Api::BackendEvent
{
    switch (notificationCode)
    {
    case BN_CLICKED:
        return { .type = Api::Events::Click };

    case BN_SETFOCUS:
        return { .type = Api::Events::Focus, .value = true };

    case BN_KILLFOCUS:
        return { .type = Api::Events::Focus, .value = false };

    default:
        return {};
    }
}

auto HasSubscription(const std::vector<Api::Events>& subscriptions, Api::Events event) -> bool
{
    return std::ranges::find(subscriptions, event) != subscriptions.end();
}

} // namespace

CommandRouter::CommandRouter(Api::EventHandler* handler)
    : m_handler(handler)
{
}

auto CommandRouter::setHandler(Api::EventHandler* handler) -> void
{
    m_handler = handler;
}

auto CommandRouter::on(Api::Id id, Api::Events event) -> void
{
    if (id == Api::InvalidId || event == Api::Events::Unknown)
    {
        return;
    }

    auto& events = m_subscriptions[id];

    if (!HasSubscription(events, event))
    {
        events.push_back(event);
    }
}

auto CommandRouter::dispatch(WPARAM wParam, LPARAM lParam) -> bool
{
    if (!lParam)
    {
        return false;
    }

    const auto id = static_cast<Api::Id>(LOWORD(wParam));

    auto event = ToCommandEvent(HIWORD(wParam));

    if (event.type == Api::Events::Unknown)
    {
        return false;
    }

    const auto it = m_subscriptions.find(id);

    if (it == m_subscriptions.end())
    {
        return false;
    }

    if (!HasSubscription(it->second, event.type))
    {
        return false;
    }

    if (!m_handler || !*m_handler)
    {
        return false;
    }

    event.target = id;
    (*m_handler)(event);

    return true;
}

} // namespace Blade::Backend

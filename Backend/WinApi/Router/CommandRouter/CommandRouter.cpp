#include "CommandRouter.h"


namespace Blade::Backend {

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
    if (event == Api::Events::Unknown)
    {
        return;
    }

    m_subscriptions[id] = event;
}

auto CommandRouter::dispatch(WPARAM wParam, LPARAM lParam) -> bool
{
    if (!lParam)
    {
        return false;
    }

    const auto id = static_cast<Api::Id>(LOWORD(wParam));

    const auto it = m_subscriptions.find(id);

    if (it == m_subscriptions.end())
    {
        return false;
    }

    if (!m_handler || !*m_handler)
    {
        return false;
    }

    (*m_handler)({ .target = id, .type = it->second });

    return true;
}

} // namespace Blade::Backend

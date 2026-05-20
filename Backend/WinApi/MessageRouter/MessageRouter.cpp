#include "MessageRouter.h"


namespace Blade::Backend {


auto MessageRouter::on(UINT msg, MessageHandler handler) -> void
{
    m_handlers[msg] = std::move(handler);
}

auto MessageRouter::dispatch(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
) -> std::optional<LRESULT>
{
    auto it = m_handlers.find(msg);

    if (it == m_handlers.end())
    {
        return std::nullopt;
    }

    if (!it->second)
    {
        return std::nullopt;
    }

    return it->second(
        hwnd,
        msg,
        wParam,
        lParam
    );
}


} // namespace

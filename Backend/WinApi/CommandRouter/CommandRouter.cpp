#include "CommandRouter.h"


namespace Blade::Backend {

auto CommandRouter::on(
    Api::Id id,
    Api::CallbackVoid callback
) -> void
{
    if (!callback)
    {
        return;
    }

    m_handlers[id] = std::move(callback);
}

auto CommandRouter::dispatch(
    WPARAM wParam,
    LPARAM lParam
) -> bool
{
    if (!lParam)
    {
        return false;
    }

    const auto id =
        static_cast<Api::Id>(
            LOWORD(wParam)
        );

    const auto it =
        m_handlers.find(id);

    if (it == m_handlers.end())
    {
        return false;
    }

    if (!it->second)
    {
        return false;
    }

    it->second();
    return true;
}

} // namespace Blade::Backend

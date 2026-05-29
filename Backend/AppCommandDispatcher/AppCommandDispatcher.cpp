#include "AppCommandDispatcher.h"

#include "App/AppBackend.h"

namespace Blade::Backend {

AppCommandDispatcher::AppCommandDispatcher(AppBackend* backend) : m_backend(backend)
{
}

auto AppCommandDispatcher::dispatch(const Api::AppCommand& command) -> void
{
    switch (command.command)
    {
    case Api::AppCommandType::Quit:
        if (m_backend) m_backend->quit();
        break;

    default:
        break;
    }
}

} // namespace Blade::Backend

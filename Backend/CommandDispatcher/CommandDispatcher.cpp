#include "CommandDispatcher.h"


namespace Blade::Backend {

CommandDispatcher::CommandDispatcher(Api::ApiBackend* backend) : m_backend(backend)
{
}

auto CommandDispatcher::dispatch(
    const Api::BackendCommand& command
) -> void
{
    std::wcout << "BackendCommand::" << to_string(command.command) << " -> " << command.nodeType << "\n";

    switch (command.command)
    {
    case Api::CommandType::Create:
        create(command);
        break;

    case Api::CommandType::Attach:
        attach(command);
        break;

    case Api::CommandType::Remove:
        remove(command);
        break;

    default:
        break;
    }
}

auto CommandDispatcher::create(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::attach(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::remove(const Api::BackendCommand& command) -> void
{
}


} // namespace

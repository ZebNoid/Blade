#include "CommandDispatcher.h"

#include "App/AppBackend.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {

CommandDispatcher::CommandDispatcher(AppBackend* backend) : m_backend(backend)
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
    if (command.nodeType == L"Window")
    {
        auto* nativeWindow = m_backend->windows().createWindow();

        NativeNode node = {
            .id = command.id,
            .type = command.nodeType,
            .hwnd = nativeWindow->handle(),
            .parent = command.parent,
        };

        // node.id = command.id;
        // node.type = command.nodeType;
        // node.parent = command.parent;
        // node.hwnd = nativeWindow->handle();

        m_backend->nodes().add(
            std::move(node)
        );

        return;
    }

    if (command.nodeType == L"Button")
    {
        // TODO
        return;
    }
}

auto CommandDispatcher::attach(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::remove(const Api::BackendCommand& command) -> void
{
}


} // namespace

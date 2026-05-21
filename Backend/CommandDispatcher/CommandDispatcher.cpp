#include "CommandDispatcher.h"

#include "App/AppBackend.h"
#include "Node/NativeNode/NativeNode.h"
#include "Property/NativePropertyMapper/NativePropertyMapper.h"


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
    auto node = m_backend->factory().create(command);

    if (!node)
    {
        return;
    }

    m_backend->nodes().add(
        std::move(*node)
    );

    //
    // if (command.nodeType == L"Window")
    // {
    //     auto* nativeWindow = m_backend->windows().createWindow();
    //
    //
    //     nativeWindow->router().on(
    //         WM_CLOSE,
    //         [](HWND hwnd, UINT, WPARAM, LPARAM)
    //         {
    //             DestroyWindow(hwnd);
    //             return 0;
    //         }
    //     );
    //
    //     nativeWindow->router().on(
    //         WM_DESTROY,
    //         [nativeWindow](HWND, UINT, WPARAM, LPARAM)
    //         {
    //             nativeWindow->markDead();
    //             return 0;
    //         }
    //     );
    //
    //     NativeNode node = {
    //         .id = command.id,
    //         .type = command.nodeType,
    //         .hwnd = nativeWindow->handle(),
    //         .parent = command.parent,
    //     };
    //
    //     NativePropertyMapper::apply(
    //         node,
    //         command.props
    //     );
    //
    //     m_backend->nodes().add(
    //         std::move(node)
    //     );
    //
    //     return;
    // }
    //
    // if (command.nodeType == L"Button")
    // {
    //     // TODO
    //     return;
    // }
}

auto CommandDispatcher::attach(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::remove(const Api::BackendCommand& command) -> void
{
}


} // namespace

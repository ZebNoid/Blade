#include "NativeNodeFactory.h"

#include "App/AppBackend.h"
#include "Property/NativePropertyMapper/NativePropertyMapper.h"


namespace Blade::Backend {

NativeNodeFactory::NativeNodeFactory(AppBackend* backend) : m_backend(backend)
{
}

auto NativeNodeFactory::create(
    const Api::BackendCommand& command
) -> std::optional<NativeNode>
{
    if (command.nodeType == L"Window")
    {
        return createWindow(command);
    }

    return std::nullopt;
}

auto NativeNodeFactory::createWindow(
    const Api::BackendCommand& command
) -> std::optional<NativeNode>
{
    auto* nativeWindow = m_backend->host().createWindow();

    if (!nativeWindow)
    {
        return std::nullopt;
    }

    nativeWindow->router().on(
        WM_CLOSE,
        [](HWND hwnd, UINT, WPARAM, LPARAM)
        {
            DestroyWindow(hwnd);
            return 0;
        }
    );

    nativeWindow->router().on(
        WM_DESTROY,
        [nativeWindow](HWND, UINT, WPARAM, LPARAM)
        {
            nativeWindow->markDead();
            return 0;
        }
    );

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .hwnd = nativeWindow->handle(),
        .parent = command.parent,
    };

    NativePropertyMapper::apply(
        node,
        command.props
    );

    return node;
}

} // namespace

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

    nativeWindow->applyProps(command.props);
    nativeWindow->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .hwnd = nativeWindow->handle(),
        .parent = command.parent,
    };

    return node;
}

} // namespace

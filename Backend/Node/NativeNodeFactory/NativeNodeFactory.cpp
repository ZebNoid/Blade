#include "NativeNodeFactory.h"

#include "App/AppBackend.h"
#include "Property/NativePropertyMapper/NativePropertyMapper.h"
#include "WinApi/Components/Button/NativeButton.h"


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

    if (command.nodeType == L"Button")
    {
        return createButton(command);
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
        .parent = command.parent,
        .native = std::move(nativeWindow),
    };

    return node;
}

auto NativeNodeFactory::createButton(const Api::BackendCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        return std::nullopt;
    }

    NativeButton button;

    if (!button.create(parent->native->handle()))
    {
        return std::nullopt;
    }

    button.applyProps(command.props);
    button.applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        // .native = std::move(button),
    };

    return node;
}

} // namespace

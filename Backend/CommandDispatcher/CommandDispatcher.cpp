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

    case Api::CommandType::Update:
        update(command);
        break;

    default:
        break;
    }
}

auto CommandDispatcher::create(const Api::BackendCommand& command) -> void
{
    std::wcout << "Command::" << to_string(command.command) << " [" << command.nodeType << "]\n";

    auto node = m_backend->factory().create(command);

    if (!node)
    {
        return;
    }

    m_backend->nodes().add(
        std::move(*node)
    );
}

auto CommandDispatcher::attach(const Api::BackendCommand& command) -> void
{
    auto* child = m_backend->nodes().get(command.id);
    auto* parent = m_backend->nodes().get(command.parent);

    if (!child || !parent)
    {
        return;
    }

    std::wcout << "Command::" << to_string(command.command) << " [" << child->type << " -> " << parent->type << "]\n";

    child->parent = command.parent;

    parent->native->attachChild(
        child->native.get()
    );

    // TODO dev
    // NativeApi::SetSize(child->native->handle(), {100, 50});
}

auto CommandDispatcher::remove(const Api::BackendCommand& command) -> void
{
    m_backend->nodes().remove(
        command.id
    );
}

auto CommandDispatcher::update(
    const Api::BackendCommand& command
) -> void
{
    auto* node = m_backend->nodes().get(command.id);

    if (!node)
    {
        return;
    }

    if (!node->native)
    {
        return;
    }

    node->native->applyProps(
        command.props
    );

    node->native->applyEvents(
        command.events
    );
}

} // namespace

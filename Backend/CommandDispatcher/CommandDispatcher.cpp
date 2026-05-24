#include "CommandDispatcher.h"

#include "App/AppBackend.h"
#include "Common/Logger.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/NativeApi/NativeApi.h"


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
    // LOGF_D(L"Command::%s %u [%s]", to_string(command.command).c_str(), command.id, command.nodeType.c_str());

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

    // LOGF_D(L"Command::%s %u [%s -> %s]", to_string(command.command).c_str(), command.id, child->type.c_str(), parent->type.c_str());

    child->parent = command.parent;

    parent->native->attachChild(
        child->native.get()
    );

    NativeApi::BringToFront(
        child->native->handle()
    );
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

    // LOGF_D(L"Command::%s %u [%s]", to_string(command.command).c_str(), command.id, node->type.c_str());

    node->native->applyProps(
        command.props
    );

    if (node->parent != Api::InvalidId)
    {
        NativeApi::BringToFront(
            node->native->handle()
        );
    }
}

} // namespace

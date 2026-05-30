#include "CommandDispatcher.h"

#include "App/AppBackend.h"
#include "Common/Logger.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

CommandDispatcher::CommandDispatcher(AppBackend* backend) : m_backend(backend)
{
}

auto CommandDispatcher::dispatch(
    const Api::ElementCommand& command
) -> void
{
    switch (command.command)
    {
    case Api::ElementCommandType::Create:
        create(command);
        break;

    case Api::ElementCommandType::Attach:
        attach(command);
        break;

    case Api::ElementCommandType::Remove:
        remove(command);
        break;

    case Api::ElementCommandType::Update:
        update(command);
        break;

    default:
        break;
    }
}

auto CommandDispatcher::create(const Api::ElementCommand& command) -> void
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

auto CommandDispatcher::attach(const Api::ElementCommand& command) -> void
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

    HwndApi::BringToFront(
        child->native->handle()
    );
}

auto CommandDispatcher::remove(const Api::ElementCommand& command) -> void
{
    if (auto* node = m_backend->nodes().get(command.id); node && node->native)
    {
        node->native->destroy();
    }

    m_backend->nodes().remove(
        command.id
    );
}

auto CommandDispatcher::update(
    const Api::ElementCommand& command
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
        HwndApi::BringToFront(
            node->native->handle()
        );
    }
}

} // namespace

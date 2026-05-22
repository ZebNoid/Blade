#include "CommandDispatcher.h"

#include "App/AppBackend.h"
#include "Node/NativeNode/NativeNode.h"
#include "Property/NativePropertyMapper/NativePropertyMapper.h"
#include "WinApi/NativeApi/NativeApi.h"


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
}

auto CommandDispatcher::attach(const Api::BackendCommand& command) -> void
{
    auto* child = m_backend->nodes().get(command.id);
    auto* parent = m_backend->nodes().get(command.parent);

    if (!child || !parent)
    {
        return;
    }

    child->parent = command.parent;

    attachNative(
        *parent,
        *child
    );
}

auto CommandDispatcher::remove(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::attachNative(NativeNode& parent, NativeNode& child) -> void
{
    if (!parent.native || !child.native)
    {
        return;
    }

    parent.native->attachChild(
        child.native.get()
    );
    // TODO dev
    // NativeApi::SetSize(child.native->handle(), {100, 50});
}


} // namespace

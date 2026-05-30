#include "RenderCommandDispatcher.h"

#include "App/AppBackend.h"

namespace Blade::Backend {

RenderCommandDispatcher::RenderCommandDispatcher(AppBackend* backend)
    : m_backend(backend)
{
}

auto RenderCommandDispatcher::dispatch(const Api::RenderCommand& command) -> void
{
    if (!m_backend) return;

    switch (command.command)
    {
    case Api::RenderCommandType::Create:
        m_backend->renderNodes().create(command);
        break;

    case Api::RenderCommandType::Update:
        m_backend->renderNodes().update(command);
        break;

    case Api::RenderCommandType::UpdateRect:
        m_backend->renderNodes().updateRect(command.id, command.rect);
        break;

    case Api::RenderCommandType::Remove:
        m_backend->renderNodes().remove(command.id);
        break;
    }
}

} // namespace Blade::Backend

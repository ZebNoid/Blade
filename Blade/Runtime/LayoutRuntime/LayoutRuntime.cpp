#include "LayoutRuntime.h"

#include "Runtime/LayoutRuntime/LayoutPass/LayoutPass.h"


namespace Blade {

LayoutRuntime::LayoutRuntime(Api::ApiBackend* backend)
    : m_backend(backend)
{
}

auto LayoutRuntime::mount(WidgetTree tree) -> void
{
    const auto rootId = tree.id;
    m_roots.insert_or_assign(rootId, std::move(tree));

    auto& root = m_roots.at(rootId);
    auto layoutTree = LayoutPass::Compute(root, root.layout.size);

    send(m_materializer.create(root, layoutTree));
}

auto LayoutRuntime::resizeRoot(Api::Id rootId, const Api::Size& size) -> void
{
    const auto it = m_roots.find(rootId);

    if (it == m_roots.end())
    {
        return;
    }

    if (m_sending)
    {
        m_pendingResize.insert_or_assign(rootId, size);
        return;
    }

    auto layoutTree = LayoutPass::Compute(it->second, size);

    send(m_materializer.update(it->second, layoutTree, false));
}

auto LayoutRuntime::send(std::vector<Api::ElementCommand> commands) -> void
{
    if (!m_backend)
    {
        return;
    }

    const auto wasSending = m_sending;
    m_sending = true;

    for (auto& cmd : commands)
    {
        m_backend->process(cmd);
    }

    m_sending = wasSending;

    if (!m_sending)
    {
        flushResize();
    }
}

auto LayoutRuntime::flushResize() -> void
{
    if (m_pendingResize.empty())
    {
        return;
    }

    auto pending = std::move(m_pendingResize);
    m_pendingResize.clear();

    for (const auto& [rootId, size] : pending)
    {
        resizeRoot(rootId, size);
    }
}

} // namespace Blade

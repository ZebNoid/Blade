#include "LayoutRuntime.h"

#include "Runtime/LayoutRuntime/LayoutPass/LayoutPass.h"


namespace Blade {

LayoutRuntime::LayoutRuntime(Api::ApiBackend* backend, WidgetTreeRegistry& trees)
    : m_backend(backend)
    , m_trees(trees)
{
}

auto LayoutRuntime::mount(WidgetTree tree) -> WidgetTree&
{
    auto& root = m_trees.add(std::move(tree));
    auto layoutTree = LayoutPass::Compute(root, root.layout.size);
    auto commands = m_materializer.create(root, layoutTree);

    m_layoutTrees.insert_or_assign(root.id, std::move(layoutTree));
    send(std::move(commands));

    return root;
}

auto LayoutRuntime::unmount(Api::Id rootId) -> void
{
    auto* root = m_trees.root(rootId);

    if (!root)
    {
        return;
    }

    send(m_materializer.remove(*root));
    m_layoutTrees.erase(rootId);
    m_pendingResize.erase(rootId);
    m_trees.remove(rootId);
}

auto LayoutRuntime::resizeRoot(Api::Id rootId, const Api::Size& size) -> void
{
    auto* root = m_trees.root(rootId);

    if (!root)
    {
        return;
    }

    if (m_sending)
    {
        m_pendingResize.insert_or_assign(rootId, size);
        return;
    }

    auto layoutTree = LayoutPass::Compute(*root, size);
    const auto previous = m_layoutTrees.find(rootId);
    std::vector<Api::ElementCommand> commands;

    if (previous == m_layoutTrees.end())
    {
        commands = m_materializer.update(*root, layoutTree, false);
    }
    else
    {
        commands = m_materializer.updateChanged(*root, previous->second, layoutTree, false);
    }

    m_layoutTrees.insert_or_assign(rootId, std::move(layoutTree));
    send(std::move(commands));
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

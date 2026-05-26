#include "LayoutRuntime.h"

#include "Runtime/LayoutRuntime/LayoutPass/LayoutPass.h"


namespace Blade {

LayoutRuntime::LayoutRuntime(Api::ApiBackend* backend)
    : m_backend(backend)
{
}

auto LayoutRuntime::mount(WidgetTree tree) -> void
{
    auto layoutTree = LayoutPass::Build(tree, tree.layout.size);

    send(m_materializer.build(tree, layoutTree));

    m_roots.insert_or_assign(tree.id, std::move(tree));
}

auto LayoutRuntime::resizeRoot(Api::Id rootId, const Api::Size& size) -> void
{
    const auto it = m_roots.find(rootId);

    if (it == m_roots.end())
    {
        return;
    }

    auto layoutTree = LayoutPass::Build(it->second, size);

    send(m_materializer.buildUpdates(it->second, layoutTree, false));
}

auto LayoutRuntime::send(std::vector<Api::BackendCommand> commands) -> void
{
    if (!m_backend)
    {
        return;
    }

    for (auto& cmd : commands)
    {
        m_backend->process(cmd);
    }
}

} // namespace Blade

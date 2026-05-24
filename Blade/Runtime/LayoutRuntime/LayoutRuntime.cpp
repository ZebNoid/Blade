#include "LayoutRuntime.h"

#include "Runtime/LayoutEngine/Data/LayoutContext.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"
#include "Runtime/LayoutEngine/LayoutTreeBuilder/LayoutTreeBuilder.h"


namespace Blade {

LayoutRuntime::LayoutRuntime(Api::ApiBackend* backend)
    : m_backend(backend)
{
}

auto LayoutRuntime::mount(WidgetTree tree) -> void
{
    auto layoutTree = layout(tree, tree.layout.size);

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

    auto layoutTree = layout(it->second, size);

    send(m_materializer.buildUpdates(it->second, layoutTree, false));
}

auto LayoutRuntime::layout(const WidgetTree& tree, const Api::Size& available) -> LayoutNode
{
    auto layoutTree = LayoutTreeBuilder::Build(tree);
    layoutTree.layout.size = available;

    LayoutContext measureCtx{
        .node = &layoutTree,
        .available = available
    };

    LayoutEngine::Measure(measureCtx);

    LayoutContext arrangeCtx{
        .node = &layoutTree,
        .rect = {
            0,
            0,
            available.width,
            available.height
        }
    };

    LayoutEngine::Arrange(arrangeCtx);

    return layoutTree;
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

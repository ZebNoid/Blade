#include "LayoutRuntime.h"

#include "Runtime/LayoutEngine/Data/LayoutContext.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"
#include "Runtime/LayoutEngine/LayoutTreeBuilder/LayoutTreeBuilder.h"


namespace Blade {

LayoutRuntime::LayoutRuntime(
    Api::ApiBackend* backend
)
    : m_backend(backend)
{
}

auto LayoutRuntime::mount(
    WidgetTree tree
) -> void
{
    m_runtimeTree.assignIds(tree);
    registerEvents(tree);

    auto layoutTree = layout(
        tree,
        tree.layout.size
    );

    send(
        m_materializer.build(
            tree,
            layoutTree
        )
    );

    m_roots.insert_or_assign(
        tree.id,
        std::move(tree)
    );
}

auto LayoutRuntime::resizeRoot(
    Api::Id rootId,
    const Api::Size& size
) -> void
{
    const auto it = m_roots.find(rootId);

    if (it == m_roots.end())
    {
        return;
    }

    auto layoutTree = layout(
        it->second,
        size
    );

    send(
        m_materializer.buildUpdates(
            it->second,
            layoutTree,
            false
        )
    );
}

auto LayoutRuntime::handleEvent(
    const Api::BackendEvent& event
) -> Api::EventResult
{
    const auto nodeIt =
        m_events.find(event.target);

    if (nodeIt == m_events.end())
    {
        return {};
    }

    const auto eventIt =
        nodeIt->second.find(event.type);

    if (eventIt == nodeIt->second.end())
    {
        return {};
    }

    if (const auto* callback =
            std::get_if<Api::CallbackVoid>(&eventIt->second))
    {
        if (*callback)
        {
            (*callback)();
        }
    }

    return {};
}

auto LayoutRuntime::registerEvents(
    const WidgetTree& tree
) -> void
{
    if (!tree.events.empty())
    {
        m_events.insert_or_assign(
            tree.id,
            tree.events
        );
    }

    for (const auto& child : tree.children)
    {
        registerEvents(child);
    }
}

auto LayoutRuntime::layout(
    const WidgetTree& tree,
    const Api::Size& available
) -> LayoutNode
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

auto LayoutRuntime::send(
    std::vector<Api::BackendCommand> commands
) -> void
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

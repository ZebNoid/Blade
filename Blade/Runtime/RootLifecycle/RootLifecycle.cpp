#include "RootLifecycle.h"

namespace Blade {

RootLifecycle::RootLifecycle(
    Api::ApiBackend* backend,
    WidgetTreeRegistry& trees,
    EventRuntime& events,
    LayoutRuntime& layout
)
    : m_backend(backend)
    , m_trees(trees)
    , m_events(events)
    , m_layout(layout)
{
}

auto RootLifecycle::destroyRoot(Api::Id rootId) -> void
{
    if (m_destroyingRoots.contains(rootId)) return;

    auto* root = m_trees.root(rootId);
    if (!root) return;

    m_destroyingRoots.insert(rootId);
    m_events.unregisterTree(*root);
    m_layout.unmount(rootId);
    m_destroyingRoots.erase(rootId);

    if (!m_quitting && m_trees.ownerCount() == 0) quit();
}

auto RootLifecycle::quit() -> void
{
    if (m_quitting) return;

    m_quitting = true;

    for (const auto rootId : m_trees.rootIds())
    {
        destroyRoot(rootId);
    }

    if (m_backend)
    {
        m_backend->process({ .command = Api::AppCommandType::Quit });
    }
}

} // namespace Blade

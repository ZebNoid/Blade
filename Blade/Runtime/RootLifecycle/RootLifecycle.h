#pragma once

#include <unordered_set>

#include "Api/ApiBackend.h"
#include "Runtime/EventRuntime/EventRuntime.h"
#include "Runtime/LayoutRuntime/LayoutRuntime.h"
#include "Runtime/WidgetTreeRegistry/WidgetTreeRegistry.h"

namespace Blade {

class RootLifecycle
{
public:
    RootLifecycle(
        Api::ApiBackend* backend,
        WidgetTreeRegistry& trees,
        EventRuntime& events,
        LayoutRuntime& layout
    );

    auto destroyRoot(Api::Id rootId) -> void;
    auto quit() -> void;

private:
    Api::ApiBackend* m_backend = nullptr;
    WidgetTreeRegistry& m_trees;
    EventRuntime& m_events;
    LayoutRuntime& m_layout;
    std::unordered_set<Api::Id> m_destroyingRoots;
    bool m_quitting = false;
};

} // namespace Blade

#pragma once

#include "Api/ApiBackend.h"
#include "Base/WidgetTree.h"
#include "Runtime/Materializer/Materializer.h"
#include "Runtime/RenderRuntime/RenderRuntime.h"
#include "Runtime/WidgetTreeRegistry/WidgetTreeRegistry.h"


namespace Blade {

class LayoutRuntime
{
public:
    LayoutRuntime(Api::ApiBackend* backend, WidgetTreeRegistry& trees);

    auto mount(WidgetTree tree) -> WidgetTree&;

    auto unmount(Api::Id rootId) -> void;

    auto resizeRoot(Api::Id rootId, const Api::Size& size) -> void;

private:
    auto send(std::vector<Api::ElementCommand> commands) -> void;

    auto flushResize() -> void;

private:
    Api::ApiBackend* m_backend = nullptr;
    WidgetTreeRegistry& m_trees;
    RenderRuntime m_renderRuntime;
    std::unordered_map<Api::Id, LayoutNode> m_layoutTrees;
    std::unordered_map<Api::Id, Api::Size> m_pendingResize;
    bool m_sending = false;
};

} // namespace Blade

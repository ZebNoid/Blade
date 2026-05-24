#pragma once

#include <unordered_map>

#include "Api/ApiBackend.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"
#include "Runtime/Materializer/Materializer.h"


namespace Blade {

class LayoutRuntime
{
public:
    explicit LayoutRuntime(Api::ApiBackend* backend);

    auto mount(WidgetTree tree) -> void;

    auto resizeRoot(Api::Id rootId, const Api::Size& size) -> void;

private:
    auto layout(const WidgetTree& tree, const Api::Size& available) -> LayoutNode;

    auto send(std::vector<Api::BackendCommand> commands) -> void;

private:
    Api::ApiBackend* m_backend = nullptr;
    Materializer m_materializer;
    std::unordered_map<Api::Id, WidgetTree> m_roots;
};

} // namespace Blade

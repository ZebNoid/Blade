#pragma once

#include "Api/ApiBackend.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"

namespace Blade {

class RenderRuntime
{
public:
    explicit RenderRuntime(Api::ApiBackend* backend);

    auto create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> void;
    auto updateChanged(const WidgetTree& widgetTree, const LayoutNode& previousLayout, const LayoutNode& layoutTree) -> void;
    auto remove(const WidgetTree& widgetTree) -> void;

private:
    auto createNode(const WidgetTree& widget, const LayoutNode& layout, std::vector<Api::RenderCommand>& out, Api::Id root, Api::Id parent, int& order) -> void;
    auto updateChangedNode(const WidgetTree& widget, const LayoutNode* previousLayout, const LayoutNode& layout, std::vector<Api::RenderCommand>& out) -> void;
    auto removeNode(const WidgetTree& widget, std::vector<Api::RenderCommand>& out) -> void;
    auto send(const std::vector<Api::RenderCommand>& commands) -> void;

private:
    Api::ApiBackend* m_backend = nullptr;
};

} // namespace Blade

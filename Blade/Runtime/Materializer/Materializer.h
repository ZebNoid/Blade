#pragma once

#include "Command/ElementCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {


class Materializer
{
public:
    auto create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>;

    auto update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot = false) -> std::vector<Api::ElementCommand>;

    auto updateChanged(
        const WidgetTree& widgetTree,
        const LayoutNode& previousLayout,
        const LayoutNode& layoutTree,
        bool includeRoot = false
    ) -> std::vector<Api::ElementCommand>;

    auto remove(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>;

private:
    auto updateNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;

    auto updateChangedNode(
        const WidgetTree& widget,
        const LayoutNode* previousLayout,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;

    auto removeNode(const WidgetTree& widget, std::vector<Api::ElementCommand>& out) -> void;
};


} // namespace

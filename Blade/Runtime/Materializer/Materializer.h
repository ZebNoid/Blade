#pragma once

#include "Api/BackendCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {


class Materializer
{
public:
    auto assignIds(
        WidgetTree& widgetTree
    ) -> void;

    auto build(
        const WidgetTree& widgetTree,
        const LayoutNode& layoutTree
    ) -> std::vector<Api::BackendCommand>;

    auto buildUpdates(
        const WidgetTree& widgetTree,
        const LayoutNode& layoutTree,
        bool includeRoot = false
    ) -> std::vector<Api::BackendCommand>;

private:
    auto assignNodeIds(
        WidgetTree& widget
    ) -> void;

    auto buildNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent = Api::InvalidId
    ) -> void;

    auto buildUpdateNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;

    static auto buildRectProps(
        const LayoutNode& layout,
        const WidgetTree& widget,
        Api::Id parent
    ) -> Api::PropertyMap;

private:
    Api::Id nextId();

private:
    // TODO persistent widget IDs (assigned at construction)
    Api::Id m_nextId = 1;
};


} // namespace

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

private:
    auto createNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        const std::vector<WidgetTree>* contextMenus = nullptr,
        Api::Id dropTarget = Api::InvalidId
    ) -> void;

    auto updateNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;
};


} // namespace

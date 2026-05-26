#pragma once

#include "Api/BackendCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {


class Materializer
{
public:
    auto create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::BackendCommand>;

    auto update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot = false) -> std::vector<Api::BackendCommand>;

private:
    auto createNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent = Api::InvalidId
    ) -> void;

    auto updateNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;
};


} // namespace

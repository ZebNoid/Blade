#pragma once

#include "Api/BackendCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/LayoutNode.h"


namespace Blade {


class Materializer
{
public:
    auto build(
        const WidgetTree& widgetTree,
        const LayoutNode& layoutTree
    ) -> std::vector<Api::BackendCommand>;

private:
    auto buildNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent = Api::InvalidId
    ) -> void;

private:
    Api::Id nextId();

private:
    // TODO persistent widget IDs (assigned at construction)
    Api::Id m_nextId = 1;
};


} // namespace

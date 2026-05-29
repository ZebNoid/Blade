#pragma once

#include "Base/WidgetTree.h"
#include "Command/ElementCommand.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"

namespace Blade {

class MaterializerUpdate
{
public:
    static auto Build(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot = false) -> std::vector<Api::ElementCommand>;

    static auto BuildChanged(
        const WidgetTree& widgetTree,
        const LayoutNode& previousLayout,
        const LayoutNode& layoutTree,
        bool includeRoot = false
    ) -> std::vector<Api::ElementCommand>;

private:
    static auto updateNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;

    static auto updateChangedNode(
        const WidgetTree& widget,
        const LayoutNode* previousLayout,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        bool includeCurrent = true
    ) -> void;
};

} // namespace Blade

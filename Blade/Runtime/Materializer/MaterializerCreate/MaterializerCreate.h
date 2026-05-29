#pragma once

#include "Base/WidgetTree.h"
#include "Command/ElementCommand.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"
#include "Runtime/Materializer/MaterializerState.h"

namespace Blade {

class MaterializerCreate
{
public:
    static auto Build(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>;

private:
    static auto createNode(
        const WidgetTree& widget,
        const LayoutNode& layout,
        std::vector<Api::ElementCommand>& out,
        Api::Id parent = Api::InvalidId,
        MaterializerState state = {}
    ) -> void;
};

} // namespace Blade

#pragma once

#include "Base/WidgetTree.h"
#include "Command/ElementCommand.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"

namespace Blade {

class MaterializerRules
{
public:
    static auto IsContextArea(const WidgetTree& widget) -> bool;
    static auto HasEvent(const WidgetTree& widget, Api::Events event) -> bool;
    static auto ShouldMaterialize(const WidgetTree& widget, const LayoutNode& layout) -> bool;
    static auto ShouldMaterialize(const WidgetTree& widget) -> bool;
    static auto SameRect(const LayoutNode* previousLayout, const LayoutNode& layout) -> bool;
    static auto CreateCommand(
        const WidgetTree& widget,
        Api::Id parent,
        const std::vector<WidgetTree>* contextMenus,
        Api::Id dropTarget
    ) -> Api::ElementCommand;

private:
    static auto HasNativeDescendant(const WidgetTree& widget) -> bool;
    static auto IsNativeContextArea(const WidgetTree& widget) -> bool;
};

} // namespace Blade

#pragma once

#include "Command/ElementCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {

class MaterializerCommands
{
public:
    static auto Create(const WidgetTree& widget, Api::Id parent) -> Api::ElementCommand;
    static auto Create(const WidgetTree& widget, Api::Id parent, const Api::ContextMenus& menus) -> Api::ElementCommand;
    static auto Attach(const WidgetTree& widget, Api::Id parent) -> Api::ElementCommand;
    static auto Update(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::ElementCommand;
    static auto Visible(const WidgetTree& widget) -> Api::ElementCommand;

private:
    static auto UpdateProps(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::PropertyMap;
    static auto VisibleValue(const WidgetTree& widget) -> bool;
};

} // namespace Blade

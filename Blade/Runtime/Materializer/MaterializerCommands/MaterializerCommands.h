#pragma once

#include "Api/BackendCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {

class MaterializerCommands
{
public:
    static auto Create(const WidgetTree& widget, Api::Id parent) -> Api::BackendCommand;
    static auto Attach(const WidgetTree& widget, Api::Id parent) -> Api::BackendCommand;
    static auto Update(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::BackendCommand;
    static auto Visible(const WidgetTree& widget) -> Api::BackendCommand;

private:
    static auto UpdateProps(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::PropertyMap;
    static auto VisibleValue(const WidgetTree& widget) -> bool;
};

} // namespace Blade

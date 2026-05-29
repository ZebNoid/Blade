#pragma once

#include "Command/ElementCommand.h"
#include "Base/WidgetTree.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {


class Materializer
{
public:
    static auto Create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>;

    static auto Update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot = false) -> std::vector<Api::ElementCommand>;

    static auto UpdateChanged(
        const WidgetTree& widgetTree,
        const LayoutNode& previousLayout,
        const LayoutNode& layoutTree,
        bool includeRoot = false
    ) -> std::vector<Api::ElementCommand>;

    static auto Remove(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>;
};


} // namespace

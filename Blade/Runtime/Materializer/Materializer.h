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

    auto updateChanged(
        const WidgetTree& widgetTree,
        const LayoutNode& previousLayout,
        const LayoutNode& layoutTree,
        bool includeRoot = false
    ) -> std::vector<Api::ElementCommand>;

    auto remove(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>;
};


} // namespace

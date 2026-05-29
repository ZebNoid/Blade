#pragma once

#include <unordered_map>

#include "Base/WidgetTree.h"


namespace Blade {

class WidgetTreeRegistry
{
public:
    auto add(WidgetTree tree) -> WidgetTree&;

    auto root(Api::Id rootId) -> WidgetTree*;

    auto find(Api::Id widgetId) -> WidgetTree*;

    auto remove(Api::Id rootId) -> void;

    auto clear() -> void;

private:
    auto assignIds(WidgetTree& tree) -> void;

    auto assignNodeIds(WidgetTree& node) -> void;

    auto findIn(WidgetTree& node, Api::Id widgetId) -> WidgetTree*;

    auto nextId() -> Api::Id;

private:
    Api::Id m_nextId = 1;
    std::unordered_map<Api::Id, WidgetTree> m_roots;
};

} // namespace Blade

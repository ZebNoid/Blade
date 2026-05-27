#pragma once

#include "Base/WidgetTree.h"


namespace Blade {

class WidgetIdAssigner
{
public:
    auto assignIds(WidgetTree& tree) -> void;

private:
    auto assignNodeIds(WidgetTree& node) -> void;

    auto nextId() -> Api::Id;

private:
    Api::Id m_nextId = 1;
};

} // namespace Blade

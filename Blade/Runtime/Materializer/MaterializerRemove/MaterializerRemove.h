#pragma once

#include "Base/WidgetTree.h"
#include "Command/ElementCommand.h"

namespace Blade {

class MaterializerRemove
{
public:
    static auto Build(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>;

private:
    static auto removeNode(const WidgetTree& widget, std::vector<Api::ElementCommand>& out) -> void;
};

} // namespace Blade

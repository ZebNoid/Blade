#pragma once

#include "Menu/MenuTrigger.h"
#include "Runtime/Normalize/PropsVisitor.h"

namespace Blade {

struct MenuProps
{
    Api::MenuTrigger trigger = Api::MenuTrigger::RightClick;

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::MenuTrigger, trigger);
    }
};

} // namespace Blade

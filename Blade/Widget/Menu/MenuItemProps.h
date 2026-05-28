#pragma once

#include "Common/Shortcut.h"
#include "Runtime/Normalize/PropsVisitor.h"

namespace Blade {

struct MenuItemProps
{
    Api::Shortcut shortcut = Api::Shortcut::None();

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Shortcut, shortcut);
    }
};

} // namespace Blade

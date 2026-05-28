#pragma once

#include "Common/Callbacks.h"
#include "Runtime/Normalize/EventVisitor.h"

namespace Blade {

struct MenuItemEvents
{
    Api::CallbackVoid click = nullptr;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(Api::Events::Click, click);
    }
};

} // namespace Blade

#pragma once

#include "Callback/Callbacks.h"
#include "Runtime/Normalize/EventVisitor.h"

namespace Blade {

struct MenuItemEvents
{
    Api::EventCallback click;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(Api::Events::Click, click);
    }
};

} // namespace Blade

#pragma once

#include "Runtime/Normalize/EventVisitor.h"

namespace Blade {

struct TrayEvents
{
    Api::EventCallback click;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(Api::Events::Click, click);
    }
};

} // namespace Blade

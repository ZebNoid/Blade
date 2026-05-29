#pragma once

#include "Common/Callbacks.h"
#include "Runtime/Normalize/EventVisitor.h"

namespace Blade {

struct ContextAreaEvents
{
    Api::EventCallback drop;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(Api::Events::Drop, drop);
    }
};

} // namespace Blade

#pragma once
#include "Runtime/Normalize/EventVisitor.h"


namespace Blade {


struct ButtonEvents
{
    Api::EventCallback click;
    Api::EventCallback focus;
    Api::EventCallback drop;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(Api::Events::Click, click);
        v.set(Api::Events::Focus, focus);
        v.set(Api::Events::Drop, drop);
    }
};


} // namespace

#pragma once
#include "Common/Callbacks.h"
#include "Runtime/Normalize/EventVisitor.h"


namespace Blade {


struct WindowEvents
{
    Api::CallbackResult close = nullptr;
    Api::CallbackString drop = nullptr;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(Api::Events::Close, close);
        v.set(Api::Events::Drop, drop);
    }
};


} // namespace

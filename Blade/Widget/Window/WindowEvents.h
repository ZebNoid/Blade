#pragma once
#include "Common/Callbacks.h"
#include "Runtime/Normalize/EventVisitor.h"


namespace Blade {


struct WindowEvents
{
    Api::CallbackVoid close = nullptr;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(L"close", close);
    }
};


} // namespace

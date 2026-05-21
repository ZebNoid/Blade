#pragma once
#include "Runtime/Normalize/EventVisitor.h"


namespace Blade {


struct ButtonEvents
{
    Api::CallbackVoid click = nullptr;

    auto visit(EventVisitor& v) const -> void
    {
        v.set(L"click", click);
    }
};


} // namespace

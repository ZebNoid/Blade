#pragma once

#include <windows.h>

#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::Blade {


class InputHandler
{
public:
    static auto Handle(
        NativeWindow& window,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
    ) -> LRESULT;
};


} // namespace

#pragma once

#include <windows.h>

#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::WinApi {


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

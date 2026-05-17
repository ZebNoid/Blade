#pragma once

#include <windows.h>

#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::WinApi {


class CommandHandler
{
public:
    static auto Handle(
        NativeWindow& window,
        WPARAM wParam,
        LPARAM lParam
    ) -> LRESULT;

};


} // namespace

#pragma once

#include <windows.h>

#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::WinApi {


class PaintHandler
{
public:
    static auto Handle(NativeWindow& window, WPARAM wParam, LPARAM lParam) -> LRESULT;
};


} // namespace

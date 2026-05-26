#pragma once

#include <windows.h>

#include "Common/CaptionProps.h"


namespace Blade::Backend {

class NativeWindowApi
{
public:
    static auto SetCaption(HWND hwnd, const Api::CaptionProps& caption) -> void;
};

} // namespace Blade::Backend

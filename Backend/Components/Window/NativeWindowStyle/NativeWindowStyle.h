#pragma once

#include <windows.h>

#include "Window/CaptionProps.h"

namespace Blade::Backend {

class NativeWindowStyle
{
public:
    static auto SetCaption(HWND hwnd, const Api::CaptionProps& caption) -> void;
    static auto SetResizable(HWND hwnd, bool resizable) -> void;
    static auto SetTaskbar(HWND hwnd, bool taskbar) -> void;
};

} // namespace Blade::Backend

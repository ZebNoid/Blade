#pragma once

#include <windows.h>

#include "Common/CaptionProps.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/WindowPlacementProps.h"
#include "Common/WindowState.h"


namespace Blade::Backend {

class NativeWindowApi
{
public:
    static auto SetCaption(HWND hwnd, const Api::CaptionProps& caption) -> void;
    static auto SetPlacement(HWND hwnd, const Api::WindowPlacementProps& placement) -> void;
    static auto SetResizable(HWND hwnd, bool resizable) -> void;
    static auto SetTaskbar(HWND hwnd, bool taskbar) -> void;
    static auto SetTopMost(HWND hwnd, bool topMost) -> void;
    static auto SetState(HWND hwnd, Api::WindowState state) -> void;
};

} // namespace Blade::Backend

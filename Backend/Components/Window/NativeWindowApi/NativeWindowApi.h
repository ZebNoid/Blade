#pragma once

#include <windows.h>

#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "Common/WindowPlacementProps.h"
#include "Common/WindowState.h"


namespace Blade::Backend {

class NativeWindowApi
{
public:
    static auto SetIcon(HWND hwnd, const Api::Text& icon) -> HICON;
    static auto SetPlacement(HWND hwnd, const Api::WindowPlacementProps& placement) -> void;
    static auto SetNormalPlacement(HWND hwnd, const Api::WindowPlacementProps& placement, const Api::Size& windowSize) -> void;
    static auto SetNormalRect(HWND hwnd, const Api::Rect& rect) -> void;
    static auto SetTopMost(HWND hwnd, bool topMost) -> void;
    static auto SetState(HWND hwnd, Api::WindowState state) -> void;
};

} // namespace Blade::Backend

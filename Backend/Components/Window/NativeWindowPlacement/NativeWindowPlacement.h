#pragma once

#include <windows.h>

#include "Geometry/Rect.h"
#include "Geometry/Size.h"
#include "Window/WindowPlacementProps.h"

namespace Blade::Backend {

class NativeWindowPlacement
{
public:
    static auto ToRect(HWND hwnd, const Api::WindowPlacementProps& placement) -> Api::Rect;
    static auto ToRect(const Api::WindowPlacementProps& placement, Api::Size size) -> Api::Rect;
    static auto ToWinRect(const Api::Rect& rect) -> RECT;
};

} // namespace Blade::Backend

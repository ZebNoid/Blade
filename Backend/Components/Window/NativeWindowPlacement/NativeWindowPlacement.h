#pragma once

#include <windows.h>

#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/WindowPlacementProps.h"

namespace Blade::Backend {

class NativeWindowPlacement
{
public:
    static auto ToRect(HWND hwnd, const Api::WindowPlacementProps& placement) -> Api::Rect;
    static auto ToRect(const Api::WindowPlacementProps& placement, Api::Size size) -> Api::Rect;
    static auto ToWinRect(const Api::Rect& rect) -> RECT;
};

} // namespace Blade::Backend

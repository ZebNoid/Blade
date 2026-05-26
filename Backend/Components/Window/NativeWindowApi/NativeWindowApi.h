#pragma once

#include <windows.h>

#include "Common/CaptionProps.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/WindowPlacementProps.h"


namespace Blade::Backend {

class NativeWindowApi
{
public:
    static auto SetCaption(HWND hwnd, const Api::CaptionProps& caption) -> void;
    static auto SetPlacement(HWND hwnd, const Api::WindowPlacementProps& placement) -> void;
};

} // namespace Blade::Backend

#pragma once

#include <windows.h>

namespace Blade::Backend {

class AppBackend;

class WindowSurfacePainter
{
public:
    static auto PaintBuffered(HWND hwnd, HDC target, AppBackend& backend) -> void;
};

} // namespace Blade::Backend

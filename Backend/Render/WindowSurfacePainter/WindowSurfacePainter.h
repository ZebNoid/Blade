#pragma once

#include <windows.h>

namespace Blade::Backend {

class AppBackend;

namespace Surface::Painter {
    auto PaintBuffered(HWND hwnd, HDC target, AppBackend& backend) -> void;
} // namespace Surface::Painter

} // namespace Blade::Backend

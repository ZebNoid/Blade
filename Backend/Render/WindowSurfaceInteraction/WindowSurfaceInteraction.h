#pragma once

#include <windows.h>

#include "Geometry/Point.h"
#include "Menu/MenuTrigger.h"
#include "Render/WindowSurfaceHitTest/WindowSurfaceHitTest.h"

namespace Blade::Backend {

class AppBackend;

auto SetDragOver(AppBackend& backend, HWND hwnd, SurfaceHit hit, bool active) -> void;
auto SetHover(AppBackend& backend, HWND hwnd, SurfaceHit hit, bool hovered) -> void;
auto SetFocus(AppBackend& backend, HWND hwnd, SurfaceHit hit, bool focused) -> void;
auto MouseDown(AppBackend& backend, HWND hwnd, SurfaceHit hit) -> void;
auto MouseUp(AppBackend& backend, HWND hwnd, SurfaceHit hit) -> void;
auto ShowContextMenu(AppBackend& backend, HWND hwnd, Api::Point point, POINT screenPoint, Api::MenuTrigger trigger) -> bool;

} // namespace Blade::Backend

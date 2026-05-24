#pragma once

#include <windows.h>


namespace Blade::Backend {


auto CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;


} // namespace

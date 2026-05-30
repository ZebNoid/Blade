#include "NativeButtonApi.h"

namespace Blade::Backend {

auto NativeButtonApi::SetStyle(HWND hwnd, DWORD style, int redraw) -> void
{
    SendMessage(hwnd, BM_SETSTYLE, static_cast<WPARAM>(style), static_cast<LPARAM>(redraw));
}

} // namespace Blade::Backend

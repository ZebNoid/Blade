#include "NativeApi.h"


namespace Blade::Backend {


auto NativeApi::SetTitle(
    HWND hwnd,
    const Api::Text& text
) -> void
{
    SetWindowTextW(hwnd, text.c_str());
}

auto NativeApi::SetSize(
    HWND hwnd,
    const Api::Size& size
) -> void
{
    SetWindowPos(hwnd, nullptr, 0, 0, size.width, size.height, SWP_NOMOVE | SWP_NOZORDER);
}

auto NativeApi::SetPosition(HWND hwnd, const Api::Point& position) -> void
{
    SetWindowPos(hwnd, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


} // namespace

#include "NativeApi.h"


namespace Blade::Backend {


auto NativeApi::setTitle(
    HWND hwnd,
    const Api::Text& text
) -> void
{
    SetWindowTextW(
        hwnd,
        text.c_str()
    );
}

auto NativeApi::setSize(
    HWND hwnd,
    const Api::Size& size
) -> void
{
    SetWindowPos(
        hwnd,
        nullptr,
        0,
        0,
        size.width,
        size.height,
        SWP_NOMOVE | SWP_NOZORDER
    );
}


} // namespace

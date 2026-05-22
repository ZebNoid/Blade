#include "NativeButton.h"

#include "WinApi/Hwnd/Hwnd.h"


namespace Blade::Backend {


auto NativeButton::create(HWND parent) -> bool
{
    // TODO system font create_system_ui_font
    m_hwnd = Hwnd::Create({
        .className = TEXT("BUTTON"),
        .windowName = TEXT("Button"),
        .parent = parent,
        .style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    });

    return m_hwnd != nullptr;
}

auto NativeButton::handle() const -> HWND
{
    return m_hwnd;
}


} // namespace

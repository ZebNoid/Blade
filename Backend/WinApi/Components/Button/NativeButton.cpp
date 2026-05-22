#include "NativeButton.h"

#include "Property/NativePropertyMapper/NativePropertyMapper.h"
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
        .hInstance = GetModuleHandle(nullptr),
    });

    return m_hwnd != nullptr;
}

auto NativeButton::handle() const -> HWND
{
    return m_hwnd;
}

auto NativeButton::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    NativePropertyMapper::Apply(m_hwnd, propertyMap);
}

auto NativeButton::applyEvents(const Api::EventMap& eventMap) -> void
{
    // TODO later. there is no WM_COMMAND router
}

auto NativeButton::isAlive() const -> bool
{
    return true; // TODO later
}


} // namespace

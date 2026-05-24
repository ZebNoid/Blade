#include "NativeButton.h"

#include "Property/NativePropertyMapper/NativePropertyMapper.h"
#include "WinApi/Hwnd/Hwnd.h"
#include "WinApi/Window/NativeWindow.h"


namespace Blade::Backend {


auto NativeButton::create(
    NativeWindow* parent,
    Api::Id id
) -> bool
{
    m_parent = parent;
    m_id = id;

    // TODO system font create_system_ui_font
    m_hwnd = Hwnd::Create({
        .className = TEXT("BUTTON"),
        .windowName = TEXT("Button"),
        .parent = parent->handle(),
        .style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
        .size = {100, 50}, // TODO dev
        .menu = reinterpret_cast<HMENU>(
            static_cast<UINT_PTR>(m_id)
        ),
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
    if (!m_parent)
    {
        return;
    }

    const auto it = eventMap.find(Api::Events::Click);

    if (it == eventMap.end())
    {
        return;
    }

    if (const auto* callback =
        std::get_if<Api::CallbackVoid>(&it->second))
    {
        m_parent->commandRouter().on(
            m_id,
            *callback
        );
    }
}

auto NativeButton::isAlive() const -> bool
{
    return true; // TODO later
}


} // namespace

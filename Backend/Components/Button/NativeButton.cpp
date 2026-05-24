#include "NativeButton.h"

#include "Common/Logger.h"
#include "Event/EventMapper/EventMapper.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "WinApi/Hwnd/Hwnd.h"
#include "WinApi/NativeApi/NativeApi.h"
#include "WinApi/Window/NativeWindow.h"


namespace Blade::Backend {

namespace {

auto ApplyIsDefault(HWND hwnd, const Api::PropertyMap& propertyMap) -> void
{
    const auto it = propertyMap.find(Api::Props::IsDefault);

    if (it == propertyMap.end())
    {
        return;
    }

    const auto* isDefault = std::get_if<bool>(&it->second);

    if (!isDefault)
    {
        return;
    }

    const auto style = *isDefault ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON;
    NativeApi::SetStyle(hwnd, style, TRUE);
}

} // namespace


auto NativeButton::create(NativeWindow* parent, Api::Id id) -> bool
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
        .menu = reinterpret_cast<HMENU>(static_cast<UINT_PTR>(m_id)),
        .hInstance = GetModuleHandle(nullptr),
    });

    return m_hwnd != nullptr;
}

auto NativeButton::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    PropertyMapper::Apply(m_hwnd, propertyMap);
    ApplyIsDefault(m_hwnd, propertyMap);
}

auto NativeButton::applyEvents(const Api::EventSubscriptions& events) -> void
{
    EventMapper::Apply(*this, events);
}

auto NativeButton::isAlive() const -> bool
{
    return true; // TODO later
}


} // namespace

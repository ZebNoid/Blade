#include "NativeButton.h"

#include "Common/Logger.h"
#include "Event/EventMapper/EventMapper.h"
#include "Property/NativePropertyMapper/NativePropertyMapper.h"
#include "WinApi/Hwnd/Hwnd.h"
#include "WinApi/NativeApi/NativeApi.h"
#include "WinApi/Window/NativeWindow.h"


namespace Blade::Backend {


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
    NativePropertyMapper::Apply(m_hwnd, propertyMap);

    auto it = propertyMap.find(Api::Props::Default);
    if (it != propertyMap.end()) {
        auto value = it->second;
        if (const auto* b_ptr = std::get_if<bool>(&value))
        {
            // TODO not working
            bool isDefault = *b_ptr;
            auto style = isDefault ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON;
            // LOGF_E(L" -> ApplyProps::%s %d", to_string(Api::Props::Default).c_str(), isDefault);
            NativeApi::SetStyle(m_hwnd, style, TRUE);
        }
    }
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

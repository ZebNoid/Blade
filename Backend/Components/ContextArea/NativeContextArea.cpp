#include "NativeContextArea.h"

#include "Components/Window/NativeWindow.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "Property/PropertyReader.h"
#include "WinApi/Window/Hwnd/Hwnd.h"

namespace Blade::Backend {

auto NativeContextArea::create(NativeWindow* parent, Api::Id id) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;

    m_hwnd = Hwnd::Create({
        .className = L"STATIC",
        .windowName = L"",
        .parent = parent->handle(),
        .style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_NOTIFY,
        .menu = reinterpret_cast<HMENU>(static_cast<UINT_PTR>(m_id)),
        .hInstance = GetModuleHandle(nullptr),
    });

    return m_hwnd != nullptr;
}

auto NativeContextArea::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus))
    {
        enableContextMenus(*menus);
    }

    PropertyMapper::Apply(m_hwnd, propertyMap);
}

auto NativeContextArea::applyEvents(const Api::EventSubscriptions&) -> void
{
}

auto NativeContextArea::isAlive() const -> bool
{
    return true;
}

auto NativeContextArea::attachChild(INativeElement*) -> void
{
}

auto NativeContextArea::enableContextMenus(Api::ContextMenus menus) -> void
{
    if (m_contextMenu || !m_hwnd || menus.empty()) return;

    auto* parent = dynamic_cast<NativeWindow*>(m_parent);
    if (!parent) return;

    auto contextMenu = std::make_unique<NativeContextMenu>();
    if (contextMenu->attach(m_hwnd, m_id, parent->commandRouter(), std::move(menus))) m_contextMenu = std::move(contextMenu);
}

} // namespace Blade::Backend

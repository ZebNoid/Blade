#include "NativeButton.h"

#include "Common/Logger.h"
#include "Components/Button/NativeButtonProps.h"
#include "Event/EventMapper/EventMapper.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "Property/PropertyReader.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Window/Hwnd/Hwnd.h"
#include "Components/Window/NativeWindow.h"


namespace Blade::Backend {

auto NativeButton::create(NativeWindow* parent, Api::Id id, const NativeCreateContext& context) -> bool
{
    m_parent = parent;
    m_id = id;

    m_hwnd = Hwnd::Create({
        .className = TEXT("BUTTON"),
        .windowName = TEXT("Button"),
        .parent = parent->handle(),
        .style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_PUSHBUTTON | BS_NOTIFY,
        .size = {100, 50}, // TODO dev
        .menu = reinterpret_cast<HMENU>(static_cast<UINT_PTR>(m_id)),
        .hInstance = context.instance,
    });

    if (m_hwnd && context.resources) HwndApi::SetFont(m_hwnd, context.resources->defaultFont());

    return m_hwnd != nullptr;
}

auto NativeButton::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus))
    {
        enableContextMenus(*menus);
    }

    if (const auto* dropTarget = PropertyReader::Get<bool>(propertyMap, Api::Props::DropTarget); dropTarget && *dropTarget)
    {
        enableDropTarget();
    }

    PropertyMapper::Apply(m_hwnd, propertyMap);
    NativeButtonProps::Apply(m_hwnd, propertyMap);
}

auto NativeButton::applyEvents(const Api::EventSubscriptions& events) -> void
{
    EventMapper::Apply(*this, events);
}

auto NativeButton::enableDropTarget() -> void
{
    if (m_dropTarget || !m_hwnd) return;

    auto* parent = dynamic_cast<NativeWindow*>(m_parent);
    if (!parent) return;

    auto dropTarget = std::make_unique<OleDropTarget>(m_id, parent->commandRouter());
    if (dropTarget->registerHwnd(m_hwnd)) m_dropTarget = std::move(dropTarget);
}

auto NativeButton::enableContextMenus(Api::ContextMenus menus) -> void
{
    if (m_contextMenu || !m_hwnd || menus.empty()) return;

    auto* parent = dynamic_cast<NativeWindow*>(m_parent);
    if (!parent) return;

    auto contextMenu = std::make_unique<NativeContextMenu>();
    if (contextMenu->attach(m_hwnd, m_id, parent->commandRouter(), std::move(menus))) m_contextMenu = std::move(contextMenu);
}

auto NativeButton::isAlive() const -> bool
{
    return true; // TODO later
}


} // namespace

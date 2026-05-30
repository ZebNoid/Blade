#include "NativeLabel.h"

#include <algorithm>

#include "Components/Window/NativeWindow.h"
#include "Logging/Logger.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "Property/PropertyReader.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Window/Hwnd/Hwnd.h"

namespace Blade::Backend {

namespace {

auto HasEvent(const Api::EventSubscriptions& events, Api::Events event) -> bool
{
    return std::ranges::find(events, event) != events.end();
}

} // namespace

auto NativeLabel::create(NativeWindow* parent, Api::Id id, const NativeCreateContext& context) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;

    m_hwnd = Hwnd::Create({
        .className = TEXT("STATIC"),
        .windowName = TEXT(""),
        .parent = parent->handle(),
        .style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_LEFT | SS_NOTIFY,
        .size = {100, 30},
        .menu = reinterpret_cast<HMENU>(static_cast<UINT_PTR>(m_id)),
        .hInstance = context.instance,
    });

    if (m_hwnd && context.resources) HwndApi::SetFont(m_hwnd, context.resources->defaultFont());

    return m_hwnd != nullptr;
}

auto NativeLabel::applyProps(const Api::PropertyMap& propertyMap) -> void
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
}

auto NativeLabel::applyEvents(const Api::EventSubscriptions& events) -> void
{
    if (HasEvent(events, Api::Events::Drop)) enableDropTarget();

    auto* parent = dynamic_cast<NativeWindow*>(m_parent);
    if (!parent) return;

    if (HasEvent(events, Api::Events::Click))
    {
        parent->commandRouter().on(m_id, STN_CLICKED, { .type = Api::Events::Click });
    }
}

auto NativeLabel::isAlive() const -> bool
{
    return true; // TODO later
}

auto NativeLabel::attachChild(INativeElement*) -> void
{
}

auto NativeLabel::enableDropTarget() -> void
{
    if (m_dropTarget || !m_hwnd) return;

    auto* parent = dynamic_cast<NativeWindow*>(m_parent);
    if (!parent) return;

    auto dropTarget = std::make_unique<OleDropTarget>(m_id, parent->commandRouter());
    if (dropTarget->registerHwnd(m_hwnd)) m_dropTarget = std::move(dropTarget);
}

auto NativeLabel::enableContextMenus(Api::ContextMenus menus) -> void
{
    if (m_contextMenu || !m_hwnd || menus.empty()) return;

    auto* parent = dynamic_cast<NativeWindow*>(m_parent);
    if (!parent) return;

    auto contextMenu = std::make_unique<NativeContextMenu>();
    if (contextMenu->attach(m_hwnd, m_id, parent->commandRouter(), std::move(menus))) m_contextMenu = std::move(contextMenu);
}

} // namespace Blade::Backend

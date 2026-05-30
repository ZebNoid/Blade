#include "NativeCustom.h"

#include <algorithm>

#include "Components/Window/NativeWindow.h"
#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Menu/NativeContextMenu/NativeContextMenu.h"
#include "WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

auto HasEvent(const Api::EventSubscriptions& events, Api::Events event) -> bool
{
    return std::ranges::find(events, event) != events.end();
}

} // namespace

auto NativeCustom::create(NativeWindow* parent, Api::Id id, const NativeCreateContext& context) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    m_hwnd = parent->handle();

    return m_hwnd != nullptr;
}

auto NativeCustom::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect)) m_rect = *rect;
    if (const auto* visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible)) m_visible = *visible;
    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus)) m_contextMenus = *menus;
    if (const auto* dropTarget = PropertyReader::Get<bool>(propertyMap, Api::Props::DropTarget); dropTarget && *dropTarget) m_emitDrop = true;

    HwndApi::Invalidate(m_hwnd);
}

auto NativeCustom::applyEvents(const Api::EventSubscriptions& events) -> void
{
    m_emitClick = HasEvent(events, Api::Events::Click);
    m_emitFocus = HasEvent(events, Api::Events::Focus);
    if (HasEvent(events, Api::Events::Drop)) m_emitDrop = true;
}

auto NativeCustom::isAlive() const -> bool
{
    return true;
}

auto NativeCustom::attachChild(INativeElement*) -> void
{
}

auto NativeCustom::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!m_visible) return;

    const auto* node = renderNodes.get(m_id);
    if (!node) return;

    GdiPlusRenderApi::Draw(hdc, m_rect, node->render.forState(node->state), resources);
}

auto NativeCustom::hitTest(Api::Point point) const -> bool
{
    if (!m_visible) return false;
    return point.x >= m_rect.x
        && point.y >= m_rect.y
        && point.x < m_rect.x + m_rect.width
        && point.y < m_rect.y + m_rect.height;
}

auto NativeCustom::wantsDrop() const -> bool
{
    return m_emitDrop;
}

auto NativeCustom::hasContextMenu(Api::MenuTrigger trigger) const -> bool
{
    for (const auto& menu : m_contextMenus)
    {
        if (Api::Has(menu.trigger, trigger)) return true;
    }

    return false;
}

auto NativeCustom::showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) -> bool
{
    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return false;

    return NativeContextMenu::Show(parentWindow->handle(), parentWindow->commandRouter(), m_contextMenus, trigger, screenPoint);
}

auto NativeCustom::currentRenderState() const -> Api::WidgetState
{
    if (m_dragOver) return Api::WidgetState::DragOver;
    if (m_pressed) return Api::WidgetState::Pressed;
    if (m_hovered) return Api::WidgetState::Hover;
    if (m_focused) return Api::WidgetState::Focus;
    return Api::WidgetState::Normal;
}

auto NativeCustom::hover(RenderRegistry& renderNodes, bool hovered) -> bool
{
    if (m_hovered == hovered) return false;
    m_hovered = hovered;
    return updateState(renderNodes);
}

auto NativeCustom::dragOver(RenderRegistry& renderNodes, bool active) -> bool
{
    if (m_dragOver == active) return false;
    m_dragOver = active;
    return updateState(renderNodes);
}

auto NativeCustom::mouseDown(RenderRegistry& renderNodes) -> bool
{
    m_pressed = true;
    return updateState(renderNodes);
}

auto NativeCustom::mouseUp(RenderRegistry& renderNodes) -> bool
{
    const auto wasPressed = m_pressed;
    m_pressed = false;
    const auto changed = updateState(renderNodes);
    if (wasPressed && m_emitClick) emit(Api::Events::Click);
    return changed;
}

auto NativeCustom::focus(RenderRegistry& renderNodes, bool focused) -> bool
{
    if (m_focused == focused) return false;

    m_focused = focused;
    const auto changed = updateState(renderNodes);
    if (m_emitFocus) emit(Api::Events::Focus, focused);
    return changed;
}

auto NativeCustom::updateState(RenderRegistry& renderNodes) -> bool
{
    return renderNodes.setState(m_id, currentRenderState());
}

auto NativeCustom::emit(Api::Events event, Api::EventPayload payload) -> void
{
    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return;

    parentWindow->commandRouter().emit({
        .target = m_id,
        .type = event,
        .payload = std::move(payload)
    });
}

} // namespace Blade::Backend

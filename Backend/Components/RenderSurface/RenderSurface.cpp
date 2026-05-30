#include "RenderSurface.h"

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

auto RenderSurface::create(NativeWindow* parent, Api::Id id, const NativeCreateContext& context) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    m_hwnd = parent->handle();

    return m_hwnd != nullptr;
}

auto RenderSurface::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect)) m_rect = *rect;
    if (const auto* visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible)) m_state.visible = *visible;
    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus)) m_contextMenus = *menus;
    if (const auto* dropTarget = PropertyReader::Get<bool>(propertyMap, Api::Props::DropTarget); dropTarget && *dropTarget) m_events.drop = true;

    HwndApi::Invalidate(m_hwnd);
}

auto RenderSurface::applyEvents(const Api::EventSubscriptions& events) -> void
{
    m_events.click = HasEvent(events, Api::Events::Click);
    m_events.focus = HasEvent(events, Api::Events::Focus);
    if (HasEvent(events, Api::Events::Drop)) m_events.drop = true;
}

auto RenderSurface::isAlive() const -> bool
{
    return true;
}

auto RenderSurface::attachChild(INativeElement*) -> void
{
}

auto RenderSurface::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!m_state.visible) return;

    const auto* node = renderNodes.get(m_id);
    if (!node) return;

    GdiPlusRenderApi::Draw(hdc, m_rect, node->render.forState(node->state), resources);
}

auto RenderSurface::hitTest(Api::Point point) const -> bool
{
    if (!m_state.visible) return false;
    return point.x >= m_rect.x
        && point.y >= m_rect.y
        && point.x < m_rect.x + m_rect.width
        && point.y < m_rect.y + m_rect.height;
}

auto RenderSurface::wantsDrop() const -> bool
{
    return m_events.drop;
}

auto RenderSurface::hasContextMenu(Api::MenuTrigger trigger) const -> bool
{
    for (const auto& menu : m_contextMenus)
    {
        if (Api::Has(menu.trigger, trigger)) return true;
    }

    return false;
}

auto RenderSurface::showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) -> bool
{
    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return false;

    return NativeContextMenu::Show(parentWindow->handle(), parentWindow->commandRouter(), m_contextMenus, trigger, screenPoint);
}

auto RenderSurface::currentRenderState() const -> Api::WidgetState
{
    if (m_state.dragOver) return Api::WidgetState::DragOver;
    if (m_state.pressed) return Api::WidgetState::Pressed;
    if (m_state.hovered) return Api::WidgetState::Hover;
    if (m_state.focused) return Api::WidgetState::Focus;
    return Api::WidgetState::Normal;
}

auto RenderSurface::hover(RenderRegistry& renderNodes, bool hovered) -> bool
{
    if (m_state.hovered == hovered) return false;
    m_state.hovered = hovered;
    return updateState(renderNodes);
}

auto RenderSurface::dragOver(RenderRegistry& renderNodes, bool active) -> bool
{
    if (m_state.dragOver == active) return false;
    m_state.dragOver = active;
    return updateState(renderNodes);
}

auto RenderSurface::mouseDown(RenderRegistry& renderNodes) -> bool
{
    m_state.pressed = true;
    return updateState(renderNodes);
}

auto RenderSurface::mouseUp(RenderRegistry& renderNodes) -> bool
{
    const auto wasPressed = m_state.pressed;
    m_state.pressed = false;
    const auto changed = updateState(renderNodes);
    if (wasPressed && m_events.click) emit(Api::Events::Click);
    return changed;
}

auto RenderSurface::focus(RenderRegistry& renderNodes, bool focused) -> bool
{
    if (m_state.focused == focused) return false;

    m_state.focused = focused;
    const auto changed = updateState(renderNodes);
    if (m_events.focus) emit(Api::Events::Focus, focused);
    return changed;
}

auto RenderSurface::updateState(RenderRegistry& renderNodes) -> bool
{
    return renderNodes.setState(m_id, currentRenderState());
}

auto RenderSurface::emit(Api::Events event, Api::EventPayload payload) -> void
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

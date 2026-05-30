#include "LabelSurface.h"

#include <algorithm>

#include "Components/Window/NativeWindow.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/Menu/NativeContextMenu/NativeContextMenu.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

auto HasEvent(const Api::EventSubscriptions& events, Api::Events event) -> bool
{
    return std::ranges::find(events, event) != events.end();
}

} // namespace

auto LabelSurface::create(NativeWindow* parent, Api::Id id, const NativeCreateContext&) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    m_hwnd = parent->handle();
    return m_hwnd != nullptr;
}

auto LabelSurface::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* text = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Title)) m_text = *text;
    if (const auto* rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect)) m_rect = *rect;
    if (const auto* visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible)) m_state.visible = *visible;
    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus)) m_contextMenus = *menus;

    HwndApi::Invalidate(m_hwnd);
}

auto LabelSurface::applyEvents(const Api::EventSubscriptions& events) -> void
{
    m_events.click = HasEvent(events, Api::Events::Click);
    m_events.focus = HasEvent(events, Api::Events::Focus);
    m_events.drop = HasEvent(events, Api::Events::Drop);
}

auto LabelSurface::isAlive() const -> bool
{
    return true;
}

auto LabelSurface::attachChild(INativeElement*) -> void
{
}

auto LabelSurface::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!m_state.visible) return;

    const auto* node = renderNodes.get(m_id);
    if (node) GdiPlusRenderApi::Draw(hdc, m_rect, node->render.forState(node->state), resources);

    const auto color = node ? RenderApi::TextColor(node->render.forState(node->state), resources.windowTextColor()) : resources.windowTextColor();
    RenderApi::Text(hdc, m_text, m_rect, resources.defaultFont(), color);
}

auto LabelSurface::hitTest(Api::Point point) const -> bool
{
    if (!m_state.visible) return false;
    return point.x >= m_rect.x
        && point.y >= m_rect.y
        && point.x < m_rect.x + m_rect.width
        && point.y < m_rect.y + m_rect.height;
}

auto LabelSurface::wantsDrop() const -> bool
{
    return m_events.drop;
}

auto LabelSurface::hasContextMenu(Api::MenuTrigger trigger) const -> bool
{
    for (const auto& menu : m_contextMenus)
    {
        if (Api::Has(menu.trigger, trigger)) return true;
    }

    return false;
}

auto LabelSurface::showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) -> bool
{
    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return false;

    return NativeContextMenu::Show(parentWindow->handle(), parentWindow->commandRouter(), m_contextMenus, trigger, screenPoint);
}

auto LabelSurface::setState(RenderRegistry& renderNodes, Api::WidgetState state) -> bool
{
    return renderNodes.setState(m_id, state);
}

auto LabelSurface::hover(RenderRegistry& renderNodes, bool hovered) -> bool
{
    if (m_state.hovered == hovered) return false;
    m_state.hovered = hovered;
    return updateState(renderNodes);
}

auto LabelSurface::dragOver(RenderRegistry& renderNodes, bool active) -> bool
{
    if (m_state.dragOver == active) return false;
    m_state.dragOver = active;
    return updateState(renderNodes);
}

auto LabelSurface::mouseDown(RenderRegistry& renderNodes) -> bool
{
    m_state.pressed = true;
    return updateState(renderNodes);
}

auto LabelSurface::mouseUp(RenderRegistry& renderNodes) -> bool
{
    const auto wasPressed = m_state.pressed;
    m_state.pressed = false;
    const auto changed = updateState(renderNodes);

    if (wasPressed && m_events.click)
    {
        auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
        if (parentWindow)
        {
            parentWindow->commandRouter().emit({
                .target = m_id,
                .type = Api::Events::Click
            });
        }
    }

    return changed;
}

auto LabelSurface::focus(RenderRegistry& renderNodes, bool focused) -> bool
{
    if (m_state.focused == focused) return false;

    m_state.focused = focused;
    const auto changed = updateState(renderNodes);

    if (m_events.focus)
    {
        auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
        if (parentWindow)
        {
            parentWindow->commandRouter().emit({
                .target = m_id,
                .type = Api::Events::Focus,
                .payload = focused
            });
        }
    }

    return changed;
}

auto LabelSurface::updateState(RenderRegistry& renderNodes) -> bool
{
    return setState(renderNodes, VisualState(m_state));
}

} // namespace Blade::Backend

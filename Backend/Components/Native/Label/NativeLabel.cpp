#include "NativeLabel.h"

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

auto NativeLabel::create(NativeWindow* parent, Api::Id id, const NativeCreateContext&) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    m_hwnd = parent->handle();
    return m_hwnd != nullptr;
}

auto NativeLabel::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* text = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Title)) m_text = *text;
    if (const auto* rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect)) m_rect = *rect;
    if (const auto* visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible)) m_visible = *visible;
    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus)) m_contextMenus = *menus;

    HwndApi::Invalidate(m_hwnd);
}

auto NativeLabel::applyEvents(const Api::EventSubscriptions& events) -> void
{
    m_emitClick = HasEvent(events, Api::Events::Click);
    m_emitFocus = HasEvent(events, Api::Events::Focus);
    m_emitDrop = HasEvent(events, Api::Events::Drop);
}

auto NativeLabel::isAlive() const -> bool
{
    return true;
}

auto NativeLabel::attachChild(INativeElement*) -> void
{
}

auto NativeLabel::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!m_visible) return;

    const auto* node = renderNodes.get(m_id);
    if (node) GdiPlusRenderApi::Draw(hdc, m_rect, node->render.forState(node->state), resources);

    const auto color = node ? RenderApi::TextColor(node->render.forState(node->state), resources.windowTextColor()) : resources.windowTextColor();
    RenderApi::Text(hdc, m_text, m_rect, resources.defaultFont(), color);
}

auto NativeLabel::hitTest(Api::Point point) const -> bool
{
    if (!m_visible) return false;
    return point.x >= m_rect.x
        && point.y >= m_rect.y
        && point.x < m_rect.x + m_rect.width
        && point.y < m_rect.y + m_rect.height;
}

auto NativeLabel::wantsDrop() const -> bool
{
    return m_emitDrop;
}

auto NativeLabel::hasContextMenu(Api::MenuTrigger trigger) const -> bool
{
    for (const auto& menu : m_contextMenus)
    {
        if (Api::Has(menu.trigger, trigger)) return true;
    }

    return false;
}

auto NativeLabel::showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) -> bool
{
    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return false;

    return NativeContextMenu::Show(parentWindow->handle(), parentWindow->commandRouter(), m_contextMenus, trigger, screenPoint);
}

auto NativeLabel::setState(RenderRegistry& renderNodes, Api::WidgetState state) -> bool
{
    return renderNodes.setState(m_id, state);
}

auto NativeLabel::mouseDown(RenderRegistry& renderNodes) -> bool
{
    m_pressed = true;
    return setState(renderNodes, Api::WidgetState::Pressed);
}

auto NativeLabel::mouseUp(RenderRegistry& renderNodes) -> bool
{
    const auto wasPressed = m_pressed;
    m_pressed = false;
    const auto changed = setState(renderNodes, m_focused ? Api::WidgetState::Focus : Api::WidgetState::Normal);

    if (wasPressed && m_emitClick)
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

auto NativeLabel::focus(RenderRegistry& renderNodes, bool focused) -> bool
{
    if (m_focused == focused) return false;

    m_focused = focused;
    const auto changed = setState(renderNodes, focused ? Api::WidgetState::Focus : Api::WidgetState::Normal);

    if (m_emitFocus)
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

} // namespace Blade::Backend

#include "NativeCustom.h"

#include <algorithm>

#include "Components/Window/NativeWindow.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

auto SetElement(HWND hwnd, LPARAM lParam) -> void
{
    const auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
}

auto GetElement(HWND hwnd) -> NativeCustom*
{
    return reinterpret_cast<NativeCustom*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

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
    m_resources = context.resources;
    m_renderNodes = context.renderNodes;
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

auto NativeCustom::onPaint(HDC hdc, const Api::Rect& rect) -> void
{
    const auto* node = m_renderNodes ? m_renderNodes->get(m_id) : nullptr;
    if (node)
    {
        const auto& render = node->render.forState(node->state);
        updateRegion(rect, RenderApi::BorderRadius(render));
        if (m_resources) GdiPlusRenderApi::Draw(hdc, rect, render, *m_resources);
        return;
    }

    updateRegion(rect, 0);
    if (m_resources) RenderApi::Fill(hdc, rect, m_resources->windowBrush());
}

auto NativeCustom::hitTest() const -> LRESULT
{
    return HTCLIENT;
}

auto NativeCustom::exStyle() const -> DWORD
{
    return 0;
}

auto NativeCustom::resources() const -> ResourceManager*
{
    return m_resources;
}

auto NativeCustom::renderNodes() const -> RenderRegistry*
{
    return m_renderNodes;
}

auto CALLBACK NativeCustom::Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    if (msg == WM_NCCREATE)
    {
        SetElement(hwnd, lParam);
        return TRUE;
    }

    auto* self = GetElement(hwnd);
    if (self)
    {
        if (auto result = self->handle(msg, wParam, lParam)) return *result;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

auto NativeCustom::handle(UINT msg, WPARAM, LPARAM) -> std::optional<LRESULT>
{
    if (msg == WM_ERASEBKGND) return TRUE;
    if (msg == WM_NCHITTEST) return hitTest();

    if (msg == WM_MOUSEMOVE)
    {
        m_hovered = true;
        trackMouseLeave();
        updateRenderState(currentRenderState());
        return {};
    }

    if (msg == WM_MOUSELEAVE)
    {
        m_trackingMouse = false;
        m_hovered = false;
        m_pressed = false;
        updateRenderState(currentRenderState());
        return {};
    }

    if (msg == WM_LBUTTONDOWN)
    {
        m_pressed = true;
        SetFocus(m_hwnd);
        updateRenderState(currentRenderState());
        return {};
    }

    if (msg == WM_LBUTTONUP)
    {
        const auto wasPressed = m_pressed;
        m_pressed = false;
        updateRenderState(currentRenderState());
        if (wasPressed && m_emitClick) emit(Api::Events::Click);
        return {};
    }

    if (msg == WM_SETFOCUS)
    {
        m_focused = true;
        updateRenderState(currentRenderState());
        if (m_emitFocus) emit(Api::Events::Focus, true);
        return {};
    }

    if (msg == WM_KILLFOCUS)
    {
        m_focused = false;
        m_pressed = false;
        updateRenderState(currentRenderState());
        if (m_emitFocus) emit(Api::Events::Focus, false);
        return {};
    }

    if (msg != WM_PAINT) return {};

    PAINTSTRUCT paint{};
    const auto hdc = BeginPaint(m_hwnd, &paint);
    onPaint(hdc, HwndApi::GetClientRect(m_hwnd));
    EndPaint(m_hwnd, &paint);
    return 0;
}

auto NativeCustom::trackMouseLeave() -> void
{
    if (m_trackingMouse) return;

    TRACKMOUSEEVENT event{
        .cbSize = sizeof(TRACKMOUSEEVENT),
        .dwFlags = TME_LEAVE,
        .hwndTrack = m_hwnd
    };

    m_trackingMouse = TrackMouseEvent(&event) == TRUE;
}

auto NativeCustom::updateRenderState(Api::WidgetState state) -> void
{
    if (!m_renderNodes || !m_renderNodes->setState(m_id, state)) return;

    HwndApi::Invalidate(m_hwnd);
    HwndApi::Update(m_hwnd);
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

auto NativeCustom::updateRegion(const Api::Rect& rect, int radius) -> void
{
    const auto size = rect.size();
    if (m_regionRadius == radius && m_regionSize.width == size.width && m_regionSize.height == size.height) return;

    m_regionRadius = radius;
    m_regionSize = size;
    HwndApi::SetRoundedRegion(m_hwnd, size, radius);
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

auto NativeCustom::enableDropTarget() -> void
{
    if (m_dropTarget || !m_hwnd) return;

    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return;

    auto dropTarget = std::make_unique<OleDropTarget>(m_id, parentWindow->commandRouter());
    if (dropTarget->registerHwnd(m_hwnd)) m_dropTarget = std::move(dropTarget);
}

auto NativeCustom::enableContextMenus(Api::ContextMenus menus) -> void
{
    if (m_contextMenu || !m_hwnd || menus.empty()) return;

    auto* parentWindow = dynamic_cast<NativeWindow*>(m_parent);
    if (!parentWindow) return;

    auto contextMenu = std::make_unique<NativeContextMenu>();
    if (contextMenu->attach(m_hwnd, m_id, parentWindow->commandRouter(), std::move(menus))) m_contextMenu = std::move(contextMenu);
}

} // namespace Blade::Backend

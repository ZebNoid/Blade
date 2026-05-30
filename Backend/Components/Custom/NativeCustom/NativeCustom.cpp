#include "NativeCustom.h"

#include "Components/Window/NativeWindow.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"
#include "WinApi/Window/Hwnd/Hwnd.h"
#include "WinApi/Window/WindowClass/WindowClass.h"

namespace Blade::Backend {

namespace {

constexpr auto ClassName = L"BladeCustom";

auto SetElement(HWND hwnd, LPARAM lParam) -> void
{
    const auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
}

auto GetElement(HWND hwnd) -> NativeCustom*
{
    return reinterpret_cast<NativeCustom*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

} // namespace

auto NativeCustom::create(NativeWindow* parent, Api::Id id, const NativeCreateContext& context) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    m_resources = context.resources;
    m_renderNodes = context.renderNodes;

    WindowClass::Register(ClassName, {.proc = Proc, .background = nullptr});

    m_hwnd = Hwnd::Create({
        .className = WindowClass::Get(ClassName),
        .windowName = L"",
        .parent = parent->handle(),
        .exStyle = exStyle(),
        .style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
        .menu = reinterpret_cast<HMENU>(static_cast<UINT_PTR>(m_id)),
        .hInstance = context.instance,
        .lpParam = this,
    });

    return m_hwnd != nullptr;
}

auto NativeCustom::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    PropertyMapper::Apply(m_hwnd, propertyMap);
    HwndApi::Invalidate(m_hwnd);
}

auto NativeCustom::applyEvents(const Api::EventSubscriptions&) -> void
{
}

auto NativeCustom::isAlive() const -> bool
{
    return true;
}

auto NativeCustom::attachChild(INativeElement*) -> void
{
}

auto NativeCustom::onPaint(HDC hdc, const Api::Rect& rect) -> void
{
    const auto* node = m_renderNodes ? m_renderNodes->get(m_id) : nullptr;
    if (node)
    {
        const auto& render = node->render.forState(node->state);
        updateRegion(rect, RenderApi::BorderRadius(render));
        if (m_resources) RenderApi::Draw(hdc, rect, render, *m_resources);
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
        m_pressed = false;
        updateRenderState(currentRenderState());
        return {};
    }

    if (msg == WM_SETFOCUS)
    {
        m_focused = true;
        updateRenderState(currentRenderState());
        return {};
    }

    if (msg == WM_KILLFOCUS)
    {
        m_focused = false;
        m_pressed = false;
        updateRenderState(currentRenderState());
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
    if (m_pressed) return Api::WidgetState::Pressed;
    if (m_hovered) return Api::WidgetState::Hover;
    if (m_focused) return Api::WidgetState::Focus;
    return Api::WidgetState::Normal;
}

auto NativeCustom::updateRegion(const Api::Rect& rect, int radius) -> void
{
    const auto size = rect.size();
    if (m_regionRadius == radius && m_regionSize.width == size.width && m_regionSize.height == size.height) return;

    m_regionRadius = radius;
    m_regionSize = size;
    HwndApi::SetRoundedRegion(m_hwnd, size, radius);
}

} // namespace Blade::Backend

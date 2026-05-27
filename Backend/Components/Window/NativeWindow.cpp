#include "NativeWindow.h"

#include "Components/Window/NativeWindowProps.h"
#include "Common/Logger.h"
#include "Event/EventMapper/EventMapper.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "WinApi/Window/Hwnd/Hwnd.h"
#include "WinApi/Window/WindowClass/WindowClass.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

#define CUSTOM_CLASS L"BladeWindow"


auto NativeWindow::create(HINSTANCE hInstance, Api::Id id) -> bool
{
    m_id = id;

    WindowClass::Register(
        CUSTOM_CLASS,
        {
            .icon = LoadIcon(hInstance, MAKEINTRESOURCE(101)),
        }
    );

    m_hwnd = Hwnd::Create({
        .className = WindowClass::Get(CUSTOM_CLASS),
        .windowName = L"Blade",
        // TODO for parent add WS_CHILD
        .style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        .hInstance = hInstance,
        .lpParam = this,
    });

    return m_hwnd != nullptr;
}

auto NativeWindow::show(int cmdShow) -> void
{
    HwndApi::Show(m_hwnd, cmdShow);
    HwndApi::Update(m_hwnd);
}

auto NativeWindow::router() -> MessageRouter&
{
    return m_router;
}

auto NativeWindow::commandRouter() -> CommandRouter&
{
    return m_commandRouter;
}

auto NativeWindow::enableDropTarget() -> void
{
    if (m_dropTarget || !m_hwnd) return;

    auto dropTarget = std::make_unique<OleDropTarget>(m_id, m_commandRouter);
    if (dropTarget->registerHwnd(m_hwnd)) m_dropTarget = std::move(dropTarget);
}

auto NativeWindow::setMinSize(const Api::Size& size) -> void
{
    m_minSize = size;
}

auto NativeWindow::setMaxSize(const Api::Size& size) -> void
{
    m_maxSize = size;
}

auto NativeWindow::applyMinMax(MINMAXINFO* info) const -> void
{
    if (!info)
    {
        return;
    }

    if (m_minSize.width > 0 || m_minSize.height > 0)
    {
        const auto size = HwndApi::ClientToWindowSize(m_hwnd, m_minSize);
        if (m_minSize.width > 0) info->ptMinTrackSize.x = size.width;
        if (m_minSize.height > 0) info->ptMinTrackSize.y = size.height;
    }

    if (m_maxSize.width > 0 || m_maxSize.height > 0)
    {
        const auto size = HwndApi::ClientToWindowSize(m_hwnd, m_maxSize);
        if (m_maxSize.width > 0) info->ptMaxTrackSize.x = size.width;
        if (m_maxSize.height > 0) info->ptMaxTrackSize.y = size.height;
    }
}

auto NativeWindow::destroy() -> void
{
    if (m_hwnd != nullptr)
    {
        HwndApi::Destroy(m_hwnd);
        m_hwnd = nullptr;
    }

    m_alive = false;
}

auto NativeWindow::markDead() -> void
{
    m_alive = false;
}

auto NativeWindow::isAlive() const -> bool
{
    return m_alive;
}

auto NativeWindow::attachChild(INativeElement* child) -> void
{
    if (!child)
    {
        LOG_E(L"[Error] NativeWindow::attachChild no child");
        return;
    }

    if (HwndApi::SetParent(child->handle(), m_hwnd) == nullptr)
    {
        LOGF_E(L"[Error] NativeWindow::attachChild [%s] %lu", CUSTOM_CLASS, GetLastError());
    }

}

auto NativeWindow::applyEvents(const Api::EventSubscriptions& events) -> void
{
    EventMapper::Apply(*this, events);
}

auto NativeWindow::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    auto nativeProps = NativeWindowProps::Apply(*this, propertyMap);
    PropertyMapper::Apply(m_hwnd, nativeProps);
}


} // namespace

#include "NativeWindow.h"

#include "Components/Window/NativeWindowProps.h"
#include "Common/Logger.h"
#include "Event/EventMapper/EventMapper.h"
#include "Property/PropertyMapper/PropertyMapper.h"
#include "WinApi/ClassRegistry/WindowClass.h"
#include "WinApi/Hwnd/Hwnd.h"
#include "WinApi/NativeApi/NativeApi.h"


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
        .style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
        .hInstance = hInstance,
        .lpParam = this,
    });

    return m_hwnd != nullptr;
}

auto NativeWindow::show(int cmdShow) -> void
{
    NativeApi::Show(m_hwnd, cmdShow);
    NativeApi::Update(m_hwnd);
}

auto NativeWindow::router() -> MessageRouter&
{
    return m_router;
}

auto NativeWindow::commandRouter() -> CommandRouter&
{
    return m_commandRouter;
}

auto NativeWindow::destroy() -> void
{
    if (m_hwnd != nullptr)
    {
        NativeApi::Destroy(m_hwnd);
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

    if (NativeApi::SetParent(child->handle(), m_hwnd) == nullptr)
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
    auto nativeProps = NativeWindowProps::Apply(m_hwnd, propertyMap);
    PropertyMapper::Apply(m_hwnd, nativeProps);
}


} // namespace

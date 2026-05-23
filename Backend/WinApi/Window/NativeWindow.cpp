#include "NativeWindow.h"

#include "Property/NativePropertyMapper/NativePropertyMapper.h"
#include "WinApi/ClassRegistry/WindowClass.h"
#include "WinApi/Hwnd/Hwnd.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

#define CUSTOM_CLASS L"BladeWindow"


auto NativeWindow::create(HINSTANCE hInstance) -> bool
{
    WindowClass::Register(
        CUSTOM_CLASS,
        {
            .icon = LoadIcon(hInstance, MAKEINTRESOURCE(101)),
        }
    );

    m_hwnd = Hwnd::Create({
        .className = WindowClass::Get(CUSTOM_CLASS),
        .windowName = L"Blade",
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

auto NativeWindow::handle() const -> HWND
{
    return m_hwnd;
}

auto NativeWindow::router() -> MessageRouter&
{
    return m_router;
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
        std::wcerr << "[Error] NativeWindow::attachChild no child" << std::endl;
        return;
    }

    if (NativeApi::SetParent(child->handle(), m_hwnd) == nullptr)
    {
        std::wcerr << "[Error] NativeWindow::attachChild [" << CUSTOM_CLASS << "] " << GetLastError() << std::endl;
    }
}

auto NativeWindow::applyEvents(const Api::EventMap& eventMap) -> void
{
    // TODO leave in applyEvents?
    m_router.on(
        WM_DESTROY,
        [this](HWND, UINT, WPARAM, LPARAM) -> int
        {
            // close default behavior
            // step 1 -> markDead
            this->markDead();
            return 0;
        }
    );

    m_router.on(
        WM_CLOSE,
        [](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            // close default behavior
            // step 2 -> DestroyWindow
            NativeApi::Destroy(hwnd);
            return 0;
        }
    );
}

auto NativeWindow::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    NativePropertyMapper::Apply(m_hwnd, propertyMap);
}


} // namespace

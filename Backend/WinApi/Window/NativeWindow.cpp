#include "NativeWindow.h"

#include "WinApi/ClassRegistry/WindowClass.h"
#include "WinApi/Hwnd/Hwnd.h"


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
        .style = WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        .position = {3200,400}, // TODO window position!!!!
        .hInstance = hInstance,
        .lpParam = this,
    });

    return m_hwnd != nullptr;
}

auto NativeWindow::show(int cmdShow) -> void
{
    ShowWindow(m_hwnd, cmdShow);
    UpdateWindow(m_hwnd);
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
        DestroyWindow(m_hwnd);
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


} // namespace

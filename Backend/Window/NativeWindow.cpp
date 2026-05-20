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
        .hInstance = hInstance,
        .lpParam = this,
    });

    // std::cout << "NativeWindow::create: " << m_hwnd << std::endl;
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


} // namespace

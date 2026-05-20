#include "AppBackend.h"

#include "WinApi/ClassRegistry/WindowClass.h"
#include "Window/NativeWindow.h"


namespace Blade::Backend {


AppBackend::AppBackend() : m_hInstance(GetModuleHandle(nullptr))
{
    WindowClass::Init(m_hInstance);
}

auto AppBackend::init() -> void
{
    createWindow();
}

auto AppBackend::runApp() -> int
{
    std::cout << "App Start!" << std::endl;

    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return static_cast<int>(m_msg.wParam);
}

auto AppBackend::quit() -> void
{
    std::cout << "App Quit!";
    PostQuitMessage(0);
}

auto AppBackend::createWindow() -> void
{
    NativeWindow wnd{};
    wnd.create(m_hInstance);
}

} // namespace

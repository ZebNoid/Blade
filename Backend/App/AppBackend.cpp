#include "AppBackend.h"


namespace Blade::Backend {


AppBackend::AppBackend() : m_hInstance(GetModuleHandle(nullptr))
{
}

auto AppBackend::init() -> void
{
}

auto AppBackend::runApp() -> int
{
    std::cout << "App Start!";
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
}

} // namespace

#include "AppBackend.h"

#include "WinApi/ClassRegistry/WindowClass.h"


namespace Blade::Backend {


AppBackend::AppBackend() : m_hInstance(GetModuleHandle(nullptr))
{
    WindowClass::Init(m_hInstance);
    m_windows.init(m_hInstance);
}

auto AppBackend::init() -> void
{
    createWindow();
    createWindow();
}

auto AppBackend::runApp() -> int
{
    return m_runtime.run();
}

auto AppBackend::quit() -> void
{
    m_runtime.quit();
}

auto AppBackend::createWindow() -> void
{
    auto* window = m_windows.createWindow();

    window->router().on(
        WM_DESTROY,
        [&](HWND, UINT, WPARAM, LPARAM)
        {
            // window->destroy();

            quit();
            return 0;
        }
    );
}


} // namespace

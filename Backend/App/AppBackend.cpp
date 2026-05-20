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
    // createWindow();
}

auto AppBackend::runApp() -> int
{
    return m_runtime.run(
        [&]
        {
            m_windows.destroyClosedWindows();

            if (m_windows.count() == 0)
            {
                quit();
            }
        }
    );
}

auto AppBackend::quit() -> void
{
    m_runtime.quit();
}

auto AppBackend::createWindow() -> void
{
    auto* window = m_windows.createWindow();

    window->router().on(
        WM_CLOSE,
        [](HWND hwnd, UINT, WPARAM, LPARAM)
        {
            DestroyWindow(hwnd);
            return 0;
        }
    );

    window->router().on(
        WM_DESTROY,
        [window](HWND, UINT, WPARAM, LPARAM)
        {
            window->markDead();
            return 0;
        }
    );
}


} // namespace

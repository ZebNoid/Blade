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
        WM_CLOSE,
        [](HWND hwnd, UINT, WPARAM, LPARAM)
        {
            std::cout << "WM_CLOSE::DestroyWindow" << std::endl;
            DestroyWindow(hwnd);

            std::cout << "WM_CLOSE::return" << std::endl;
            return 0;
        }
    );

    window->router().on(
        WM_DESTROY,
        [&](HWND, UINT, WPARAM, LPARAM)
        {
            std::cout << "WM_DESTROY::markDead" << std::endl;
            window->markDead();

            std::cout << "WM_DESTROY::destroyClosedWindows" << std::endl;
            m_windows.destroyClosedWindows();

            if (m_windows.count() == 0)
            {
                std::cout << "WM_DESTROY::quit" << std::endl;
                quit();
            }

            return 0;
        }
    );
}


} // namespace

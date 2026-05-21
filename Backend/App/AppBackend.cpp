#include "AppBackend.h"

#include "WinApi/ClassRegistry/WindowClass.h"
#include "CommandDispatcher/CommandDispatcher.h"


namespace Blade::Backend {


AppBackend::AppBackend()
    : m_hInstance(GetModuleHandle(nullptr))
      , m_dispatcher(this)
{
    std::wcout << "AppBackend::AppBackend" << "\n";
}

auto AppBackend::init() -> void
{
    WindowClass::Init(m_hInstance);
    m_windows.init(m_hInstance);
    // createWindow();
    std::wcout << "AppBackend::init" << "\n";
}

auto AppBackend::runApp() -> int
{
    std::wcout << "AppBackend::runApp" << "\n";
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

// auto AppBackend::createWindow() -> void
// {
//     auto* window = m_windows.createWindow();
//
//     window->router().on(
//         WM_CLOSE,
//         [](HWND hwnd, UINT, WPARAM, LPARAM)
//         {
//             DestroyWindow(hwnd);
//             return 0;
//         }
//     );
//
//     window->router().on(
//         WM_DESTROY,
//         [window](HWND, UINT, WPARAM, LPARAM)
//         {
//             window->markDead();
//             return 0;
//         }
//     );
// }

auto AppBackend::process(const Api::BackendCommand& command) -> void
{
    std::wcout << "AppBackend::process" << "\n";
    m_dispatcher.dispatch(command);
}

auto AppBackend::windows() -> WindowHost&
{
    return m_windows;
}

auto AppBackend::nodes() -> NodeRegistry&
{
    return m_nodes;
}

} // namespace

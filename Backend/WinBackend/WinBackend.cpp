#include "WinBackend.h"

#include "WinInit/WinInit.h"


namespace Blade::Backend {

WinBackend::WinBackend()
{
    WinInit::InitDpi();

    m_hInstance = GetModuleHandle(nullptr);
}

auto WinBackend::runApp() -> int
{
    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return static_cast<int>(m_msg.wParam);
}

auto WinBackend::createWindow(Window& window) -> void
{
    std::cout << "WinBackend::createWindow\n"; // TODO dev

    m_materializer.create(window); // TODO

    auto native = std::make_unique<WinWindow>(
        window,
        m_hInstance
    );

    native->create();

    m_windows.push_back(
        std::move(native)
    );
}

auto WinBackend::quit() -> void
{
    std::cout << "Quit!";
    PostQuitMessage(0);
}

} // namespace

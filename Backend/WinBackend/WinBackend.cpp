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

auto WinBackend::createWindow(const Blade::Window& window) -> void
{
    std::cout << "WinBackend::createWindow\n";

    // auto native = std::make_unique<WinWindow>(
    //     window
    // );
    //
    // // native->create(); // TODO
    //
    // m_windows.push_back(
    //     std::move(native)
    // );
}

} // namespace

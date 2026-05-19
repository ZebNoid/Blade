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
    std::cout << "WinBackend::createWindow" << "" <<"\n"; // TODO dev

    auto root = m_materializer.mount(window);

    if (root == nullptr)
    {
        std::cout << "WinBackend:: root == nullptr\n"; // TODO dev
        return;
    }

    auto* native = dynamic_cast<WinWindow*>(root.get());

    if (root == nullptr)
    {
        std::cout << "WinBackend:: not WinWindow\n"; // TODO dev
        return;
    }

    native->create(m_hInstance);

    m_materializer.buildChildren(window, *native);

    m_windows.push_back(std::move(root));
}

auto WinBackend::quit() -> void
{
    std::cout << "Quit!";
    PostQuitMessage(0);
}

} // namespace

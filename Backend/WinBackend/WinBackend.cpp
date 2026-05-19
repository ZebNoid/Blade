#include "WinBackend.h"

#include "Registry/ClassRegistry/ClassRegistry.h"
#include "Registry/ResourceRegistry/ResourceRegistry.h"
#include "WinInit/WinInit.h"


namespace Blade::Backend {

WinBackend::WinBackend()
{
    WinInit::InitDpi();

    m_hInstance = GetModuleHandle(nullptr);

    ResourceRegistry::Init();
    ClassRegistry::Init(m_hInstance);
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

// TODO ApiBackend::entryWidget
auto WinBackend::createWindow(Window& window) -> void
{
    auto root = m_materializer.mount(window);
    auto* nativeWindow = dynamic_cast<WinWindow*>(root.get());

    if (nativeWindow == nullptr)
    {
        std::cerr << "WinBackend::createWindow no native Window\n"; // TODO dev
        return;
    }

    nativeWindow->create(m_hInstance);
    nativeWindow->createChildren();

    m_materializer.syncLayout(window);

    m_windows.push_back(std::move(root));
}

auto WinBackend::quit() -> void
{
    std::cout << "Quit!";
    PostQuitMessage(0);
}

} // namespace

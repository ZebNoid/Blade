#include "WindowHost.h"


namespace Blade::Backend {


auto WindowHost::init(HINSTANCE hInstance) -> void
{
    m_hInstance = hInstance;
}

auto WindowHost::createWindow() -> NativeWindow*
{
    auto window = std::make_unique<NativeWindow>();

    window->create(m_hInstance);

    auto* ptr = window.get();

    m_windows.push_back(std::move(window));

    return ptr;
}

auto WindowHost::destroyClosedWindows() -> void
{
    std::erase_if(
        m_windows,
        [](const auto& window)
        {
            return !window->isAlive();
        }
    );
}

auto WindowHost::windows() -> const auto&
{
    return m_windows;
}


} // namespace

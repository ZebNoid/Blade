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

auto WindowHost::count() const -> size_t
{
    return m_windows.size();
}

auto WindowHost::windows() -> const std::vector<std::unique_ptr<NativeWindow>>&
{
    return m_windows;
}


} // namespace

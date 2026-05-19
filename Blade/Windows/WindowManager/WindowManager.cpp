#include "WindowManager.h"

#include <cassert>

#include "Windows/Window/Window.h"


namespace Blade {


auto WindowManager::bind(ApiBackend& backend) -> void
{
    m_backend = &backend;
    assert(m_backend && "WindowManager must be bound to backend before createWindows()");
}

auto WindowManager::add(std::unique_ptr<Window> window) -> void
{
    m_windows.push_back(
        std::move(window)
    );
}

auto WindowManager::createWindow(Window& window) const -> void
{
    if (!m_backend) return;
    m_backend->createWindow(window);
}

auto WindowManager::destroyWindow(Window* target) -> void
{
    // TODO WindowManager destroy window!
    std::erase_if(
        m_windows,
        [target](const std::unique_ptr<Window>& w)
        -> bool
        {
            return w.get() == target;
        }
    );

    // TODO WindowManager quit();

    std::cout << "windows count: " << m_windows.size() << "\n"; // TODO

    if (m_windows.empty())
    {
        m_backend->quit();
    }
}

auto WindowManager::createWindows() const -> void
{
    if (!m_backend) return;
    for (auto& window : m_windows)
    {
        m_backend->createWindow(*window);
        // createWindow(*window); // TODO WindowManager
    }
}

auto WindowManager::empty() const -> bool
{
    return m_windows.empty();
}


} // namespace

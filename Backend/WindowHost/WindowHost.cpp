#include "WindowHost.h"

#include <algorithm>


namespace Blade::Backend {


auto WindowHost::attach(NativeWindow* window) -> void
{
    if (!window)
    {
        return;
    }

    m_windows.push_back(window);
}

auto WindowHost::detach(NativeWindow* window) -> void
{
    std::erase(
        m_windows,
        window
    );
}

auto WindowHost::destroyClosedWindows() -> void
{
    std::erase_if(
        m_windows,
        [](NativeWindow* window)
        {
            return !window || !window->isAlive();
        }
    );
}

auto WindowHost::count() const -> size_t
{
    return m_windows.size();
}

auto WindowHost::windows() const
    -> const std::vector<NativeWindow*>&
{
    return m_windows;
}


} // namespace

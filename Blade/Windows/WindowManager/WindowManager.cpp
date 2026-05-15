#include "WindowManager.h"

#include "../Window/Window.h"

WindowManager::WindowManager(AppContext& ctx)
    : m_ctx(ctx)
{
}

auto WindowManager::NewWindow(const std::string& title) -> Window&
{
    auto window = std::unique_ptr<Window>(
        new Window(
            m_ctx,
            *this
        )
    );
    window->Create(title);
    Window& ref = *window;
    m_windows.push_back(
        std::move(window)
    );
    return ref;
}

auto WindowManager::DestroyWindow(Window* target) -> void
{
    std::erase_if(
        m_windows,
        [target](const std::unique_ptr<Window>& w)
        {
            return w.get() == target;
        }
    );

    std::cout << "windows count: " << m_windows.size() << "\n"; // TODO

    if (m_windows.empty())
    {
        PostQuitMessage(0);
    }
}

auto WindowManager::Empty() const -> bool
{
    return m_windows.empty();
}

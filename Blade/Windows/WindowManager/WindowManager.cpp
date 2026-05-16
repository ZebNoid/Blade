#include "WindowManager.h"

#include "../Window/Window.h"

WindowManager::WindowManager(AppContext& ctx)
    : m_appCtx(ctx)
{
}

auto WindowManager::createWindow(WindowBuilder&& builder) -> Window&
{
    auto window = std::unique_ptr<Window>(
        new Window(
            m_appCtx,
            *this
        )
    );

    window->set(builder.m_props);
    window->create();
    window->setRoot(std::move(builder.takeRoot()));

    auto& ref = *window;

    m_windows.push_back(
        std::move(window)
    );

    return ref;
}

auto WindowManager::destroyWindow(Window* target) -> void
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

auto WindowManager::empty() const -> bool
{
    return m_windows.empty();
}

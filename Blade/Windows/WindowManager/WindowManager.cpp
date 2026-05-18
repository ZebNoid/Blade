#include "WindowManager.h"

#include "Windows/Window/Window.h"


namespace Blade {


// WindowManager::WindowManager(AppContext& ctx)
//     : m_appCtx(ctx)
// {
// }

auto WindowManager::createWindow(WindowBuilder&& builder) -> Window&
{
    auto window = std::unique_ptr<Window>(
        new Window(
            // m_appCtx,
            // *this
        )
    );

    // TODO build
    window->set(builder.m_props);
    window->on(builder.m_events);
    window->create();
    // window->setRoot(builder.takeRoot());
    // TODO show window after? .set({.visible})?

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


} // namespace

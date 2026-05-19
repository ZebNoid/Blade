#include "Window.h"

#include "App/App.h"


namespace Blade {


auto Window::destroy() -> void
{
    if (m_app == nullptr)
    {
        std::cerr << "Window::destroy no app context\n";
        return;
    }
    m_app->wm().destroyWindow(this);
}

auto Window::resize(Size size) -> void
{
    // arrange({0, 0, size.width, size.height});
    // ->arrange({0, 0, size.width, size.height});
}

auto Window::mount(App* app) && -> void
{
    m_app = app;
    app->wm().add(
        std::make_unique<Window>(
            std::move(*this)
        )
    );
}


} // namespace

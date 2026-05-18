#include "Window.h"

#include "Backend/NativeWindow/NativeWindow.h"
#include "Context/WidgetContext.h"


namespace Blade {


// Window::Window(AppContext& appCtx, WindowManager& manager)
//     : m_manager(manager), m_appCtx(appCtx)
// {
// }

auto Window::show() -> void
{
    m_native.show();
}

auto Window::destroy() -> void
{
    // m_manager.destroyWindow(this);
}

auto Window::resize(Size size) -> void
{
    if (!m_root) return;

    m_root->arrange({0, 0, size.width, size.height});
}


} // namespace

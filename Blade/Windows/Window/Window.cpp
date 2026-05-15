#include "Window.h"

#include "../../Context/WidgetContext.h"
#include "../../Native/NativeWindow/NativeWindow.h"

Window::Window(AppContext& appCtx, WindowManager& manager)
    : m_manager(manager), m_appCtx(appCtx)
{
}

auto Window::create(const std::string& title) -> void
{
    WidgetContext w_ctx{
        nullptr, // TODO change for child windows
        &m_appCtx,
        this
    };

    m_native.create(w_ctx, this, title);
}

auto Window::onDestroy() -> void
{
    m_manager.destroyWindow(this);
}

auto Window::onResize(Size size) -> void
{
    if (!m_root) return;

    m_root->arrange({0,0,size.width, size.height});
}

auto Window::show() -> void
{
    m_native.show();
}

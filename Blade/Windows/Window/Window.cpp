#include "Window.h"

#include "../../Context/WidgetContext.h"
#include "../../Native/NativeWindow/NativeWindow.h"

Window::Window(AppContext& appCtx, WindowManager& manager)
    : m_manager(manager), m_app_ctx(appCtx)
{
}

auto Window::Create(const std::string& title) -> void
{
    WidgetContext w_ctx{
        nullptr, // TODO change for child windows
        &m_app_ctx,
        this
    };

    m_native.Create(w_ctx, this, title);
}

auto Window::show() -> void
{
    m_native.Show();
}

auto Window::OnDestroy() -> void
{
    m_manager.DestroyWindow(this);
}

auto Window::OnResize(Size size) -> void
{
    if (!m_root) return;

    m_root->Arrange({0,0,size.width, size.height});
}

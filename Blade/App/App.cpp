#include "App.h"


namespace Blade {


App::App() : m_wm(m_ctx)
{
    m_ctx.hInstance = GetModuleHandle(nullptr);
    // init();
}

auto App::run() -> int
{
    setup();

    if (!m_backend)
    {
        std::cerr << "No Backend set" << std::endl;
        return -1;
    }
    // m_nativeApp->initialize(); // todo init

    ui();
    build();

    return m_backend->run();
}

auto App::build() -> void
{
    for (auto& builder : m_windowBuilders)
    {
        m_wm.createWindow(std::move(builder));
    }
}


} // namespace

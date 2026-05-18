#include "App.h"


namespace Blade {


App::App() : m_wm(m_ctx)
{
    m_ctx.hInstance = GetModuleHandle(nullptr);
    init();
}

auto App::run() -> int
{
    m_nativeApp = std::make_unique<Backend::NativeApp>();
    m_nativeApp->initialize();

    // ui();
    //
    // build();

    return m_nativeApp->run();

    // while (GetMessage(&m_msg, nullptr, 0, 0))
    // {
    //     uiLoop();
    //     TranslateMessage(&m_msg);
    //     DispatchMessage(&m_msg);
    // }
    // return static_cast<int>(m_msg.wParam);
}

auto App::build() -> void
{
    for (auto& builder : m_windowBuilders)
    {
        m_wm.createWindow(std::move(builder));
    }
}

auto App::init() -> void
{
    // TODO Native App
    // DPI awareness
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    // Optional good practice comctl32
    INITCOMMONCONTROLSEX icc{};
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_STANDARD_CLASSES;

    InitCommonControlsEx(&icc);
}


} // namespace

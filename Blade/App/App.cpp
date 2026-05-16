#include "App.h"


App::App() : m_wm(m_ctx)
{
    m_ctx.hInstance = GetModuleHandle(nullptr);
    init();
}

auto App::run() -> int
{
    build();

    builder();

    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return static_cast<int>(m_msg.wParam);
}

auto App::builder() -> void
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

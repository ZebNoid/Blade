#include "App.h"


App::App() : wm(ctx)
{
    ctx.hInstance = GetModuleHandle(nullptr);
    Init();
}

auto App::Run() -> int
{
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

auto App::Init() -> void
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

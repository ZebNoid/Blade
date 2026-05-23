#include "AppRuntime.h"

#include "Common/Logger.h"


namespace Blade::Backend {


auto AppRuntime::run(Tick tick) -> int
{
    LOG(L"App Start!");

    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);

        if (tick)
        {
            tick();
        }
    }

    return static_cast<int>(m_msg.wParam);
}

auto AppRuntime::quit(int code) -> void
{
    LOG(L"App Quit!");

    PostQuitMessage(code);
}


} // namespace

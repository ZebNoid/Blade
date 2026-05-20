#include "AppRuntime.h"

#include <iostream>


namespace Blade::Backend {


auto AppRuntime::run() -> int
{
    std::cout << "App Start!" << std::endl;

    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }

    return static_cast<int>(m_msg.wParam);
}

auto AppRuntime::quit(int code) -> void
{
    std::cout << "App Quit!" << std::endl;

    PostQuitMessage(code);
}


} // namespace

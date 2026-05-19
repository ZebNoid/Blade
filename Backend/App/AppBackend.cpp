#include "AppBackend.h"


namespace Blade::Backend {


auto AppBackend::init() -> void
{
}

auto AppBackend::runApp() -> int
{
    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return static_cast<int>(m_msg.wParam);
}

auto AppBackend::quit() -> void
{
    std::cout << "Quit!";
    PostQuitMessage(0);
}

} // namespace

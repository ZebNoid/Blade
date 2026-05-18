#include "WinApp.h"

#include "WinInit/WinInit.h"


namespace Blade::Backend {

WinApp::WinApp()
{
    WinInit::InitDpi();
}

auto WinApp::run() -> int
{
    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return static_cast<int>(m_msg.wParam);
}

} // namespace

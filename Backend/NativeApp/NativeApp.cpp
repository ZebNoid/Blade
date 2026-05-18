#include "NativeApp.h"


namespace Blade::Backend {

auto NativeApp::run() -> int
{
    while (GetMessage(&m_msg, nullptr, 0, 0))
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
    return static_cast<int>(m_msg.wParam);
}

} // namespace

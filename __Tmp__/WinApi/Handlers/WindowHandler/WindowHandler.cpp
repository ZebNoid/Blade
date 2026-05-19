#include "WindowHandler.h"

#include "Helpers/Helpers.h"
#include "WinWindow/WinWindow.h"

namespace Blade::Backend {

auto WindowHandler::Handle(WinWindow& window, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {

    case WM_SIZE:
        {
            window.resize(WindowSize(lParam));
            return 0;
        }

    case WM_CLOSE:
        {
            // TODO check multiple windows
            DestroyWindow(window.handle());
            return 0;
        }

    case WM_DESTROY:
        window.owner()->destroy(); // TODO!!!
        return 0;
    }

    return DefWindowProc(window.handle(), msg, wParam, lParam);
}


} // namespace

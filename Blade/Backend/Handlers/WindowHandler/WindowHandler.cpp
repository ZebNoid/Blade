#include "WindowHandler.h"

#include "Backend/Helpers/Helpers.h"
#include "Backend/NativeWindow/NativeWindow.h"

namespace Blade::Backend::WinApi {

auto WindowHandler::Handle(NativeWindow& window, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
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
        window.getOwner()->destroy();
        return 0;
    }

    return DefWindowProc(window.handle(), msg, wParam, lParam);
}


} // namespace

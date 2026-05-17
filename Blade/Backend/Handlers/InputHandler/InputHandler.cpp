#include "InputHandler.h"

#include "Backend/Helpers/Helpers.h"
#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::WinApi {


auto InputHandler::Handle(NativeWindow& window, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_MOUSEMOVE: // WM_NCMOUSEMOVE ?
        {
            MousePosition(lParam);
            return 0;
        }

    case WM_LBUTTONDOWN:
        {
            return 0;
        }

    case WM_LBUTTONUP:
        {
            return 0;
        }

    case WM_KEYDOWN:
        {
            return 0;
        }

    case WM_KEYUP:
        {
            return 0;
        }

    case WM_CHAR:
        {
            return 0;
        }
    }

    return DefWindowProc(window.handle(), msg, wParam, lParam);
}


} // namespace

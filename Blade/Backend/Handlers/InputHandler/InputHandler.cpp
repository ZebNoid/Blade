#include "InputHandler.h"

#include "Backend/Helpers/Helpers.h"
#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::WinApi {


// WM_MOUSEMOVE
// WM_LBUTTONDBLCLK
// WM_LBUTTONDOWN
// WM_LBUTTONUP
// WM_RBUTTONUP
// WM_RBUTTONDBLCLK
// WM_MBUTTONDOWN
// WM_MBUTTONUP
// WM_MBUTTONDBLCLK
// WM_MOUSEWHEEL
// WM_KEYDOWN
// WM_KEYUP
// WM_CHAR

auto InputHandler::Handle(NativeWindow& window, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_MOUSEMOVE: // WM_NCMOUSEMOVE ?
        {
            auto pos = MousePosition(lParam);
            // std::cout << "move " << pos.x<< " " << pos.y << "\n";
            return 0;
        }

    case WM_LBUTTONDOWN:
        {
            std::cout << "WM_LBUTTONDOWN\n";
            return 0;
        }

    case WM_LBUTTONUP:
        {
            std::cout << "WM_LBUTTONUP\n";
            return 0;
        }

    case WM_LBUTTONDBLCLK:
        {
            std::cout << "WM_LBUTTONDBLCLK\n";
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

#include "InputHandler.h"


namespace Blade::Backend::Blade {


auto InputHandler::Handle(NativeWindow& window, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_MOUSEMOVE:
        {
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

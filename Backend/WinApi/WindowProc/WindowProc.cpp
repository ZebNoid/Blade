#include "WindowProc.h"


namespace Blade::Backend {

auto CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    // if (auto result = g_router.dispatch(
    //     hwnd,
    //     msg,
    //     wParam,
    //     lParam
    // ))
    // {
    //     return *result;
    // }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


} // namespace

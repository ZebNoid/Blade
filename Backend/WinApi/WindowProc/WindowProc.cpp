#include "WindowProc.h"

#include "Window/NativeWindow.h"


namespace Blade::Backend {


auto CALLBACK WindowProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
) -> LRESULT
{
    if (msg == WM_NCCREATE)
    {
        auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        auto* window = static_cast<NativeWindow*>(cs->lpCreateParams);

        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(window)
        );

        return TRUE;
    }

    auto* window = reinterpret_cast<NativeWindow*>(
        GetWindowLongPtr(hwnd, GWLP_USERDATA)
    );

    // std::cout << "window ptr: " << window << std::endl;
    // if (window != nullptr)
    // {
    //     std::cout << "message: " << msg << std::endl;
    // }

    if (window)
    {
        if (auto result = window->router().dispatch(
            hwnd,
            msg,
            wParam,
            lParam
        ))
        {
            if (result.has_value())
            {
                return result.value();
            }
        }
    }

    return DefWindowProc(
        hwnd,
        msg,
        wParam,
        lParam
    );
}


} // namespace

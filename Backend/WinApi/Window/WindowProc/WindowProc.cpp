#include "WindowProc.h"

#include "Components/Window/NativeWindow.h"


namespace Blade::Backend {

namespace {

auto SetWindow(HWND hwnd, LPARAM lParam) -> void
{
    const auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
    auto* window = static_cast<NativeWindow*>(cs->lpCreateParams);

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
}

auto GetWindow(HWND hwnd) -> NativeWindow*
{
    return reinterpret_cast<NativeWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

} // namespace

auto CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    if (msg == WM_NCCREATE)
    {
        SetWindow(hwnd, lParam);
        return TRUE;
    }

    auto* window = GetWindow(hwnd);

    if (window)
    {
        if (auto result = window->router().dispatch(hwnd, msg, wParam, lParam))
        {
            return result.value();
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

} // namespace Blade::Backend

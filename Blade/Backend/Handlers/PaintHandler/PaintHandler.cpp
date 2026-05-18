#include "PaintHandler.h"


namespace Blade::Backend::WinApi {


auto PaintHandler::Handle(WinWindow& window, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    if (auto* owner = window.owner())
    {
        // if (auto* root = owner->root()) // TODO!!!
        // {
        //     PAINTSTRUCT ps;
        //     auto hwnd = window.handle();
        //     HDC hdc = BeginPaint(hwnd, &ps);
        //
        //     LayoutDebugRenderer::Render(hdc, *root);
        //
        //     EndPaint(hwnd, &ps);
        // }
    }
    return 0;
}


} // namespace

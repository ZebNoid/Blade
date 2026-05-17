#include "PaintHandler.h"


namespace Blade::Backend::WinApi {


auto PaintHandler::Handle(NativeWindow& window, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    PAINTSTRUCT ps;
    auto hwnd = window.handle();
    HDC hdc = BeginPaint(hwnd, &ps);

    // LayoutDebugRenderer::Render(hdc, *window.getOwner()->m_root); // TODO root
    EndPaint(hwnd, &ps);
    return 0;
}


} // namespace

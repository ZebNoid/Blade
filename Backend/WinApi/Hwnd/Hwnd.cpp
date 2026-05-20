#include "Hwnd.h"


namespace Blade::Backend {


auto Hwnd::Create(const HwndDesc& desc) -> HWND
{
    const auto hwnd = CreateWindowEx(
        desc.exStyle,
        desc.className,
        desc.windowName,
        desc.style,
        desc.position.x, desc.position.y,
        desc.size.width, desc.size.height,
        desc.parent,
        desc.menu,
        desc.hInstance,
        desc.lpParam
    );

    if (!hwnd)
    {
        std::wcerr << "[Error] Hwnd::Create[" << desc.className << "] " << GetLastError() << std::endl;
    }

    return hwnd;
}

auto Hwnd::Style() -> DWORD
{
    return 0;
}

auto Hwnd::ExStyle() -> DWORD
{
    return 0;
}


} // namespace

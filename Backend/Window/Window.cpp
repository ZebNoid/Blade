#include "Window.h"

#include "WinApi/ClassRegistry/ClassRegistry.h"


namespace Blade::Backend {

#define CUSTOM_CLASS L"BladeWindow"

auto Window::create() -> void
{
    auto hInstance = GetModuleHandle(nullptr);

    ClassRegistry::Register(
        CUSTOM_CLASS,
        {
            .name = CUSTOM_CLASS,
            .proc = WindowProc,
            // .background = (HBRUSH)COLOR_HIGHLIGHTTEXT,
            // TODO set window icon
            .icon = LoadIcon(hInstance, MAKEINTRESOURCE(101)),
            // .icon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_APP_ICON)),
        }
    );
}


} // namespace

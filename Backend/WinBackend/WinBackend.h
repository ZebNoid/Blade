#pragma once

#include "Api/ApiBackend.h"
#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


class WinBackend : public ApiBackend
{
public:
    WinBackend();

    auto runApp() -> int override;

    auto createWindow(Window& window) -> void override;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};

    std::vector<std::unique_ptr<WinWindow>> m_windows;
};


} // namespace

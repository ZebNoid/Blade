#pragma once

#include "ApiBackend.h"
#include "WinWindow/WinWindow.h"
#include "Materializer/Materializer.h"


namespace Blade::Backend {


class WinBackend : public ApiBackend
{
public:
    WinBackend();

    auto runApp() -> int override;

    // auto createWindow(Window& window) -> void override;

    auto quit() -> void override;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};

    Materializer m_materializer;

    // std::vector<std::unique_ptr<WinWindow>> m_windows;
    std::vector<std::unique_ptr<ApiWidget>> m_windows;
};


} // namespace

#pragma once

#include "Api/ApiBackend.h"


namespace Blade::Backend {


class WinBackend : public ApiBackend
{
public:
    WinBackend();

    auto run() -> int override;

    auto createWindow(const Blade::Window& window) -> void override;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};

    std::vector<std::unique_ptr<WinWindow>> m_windows;
};


} // namespace

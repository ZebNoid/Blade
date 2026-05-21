#pragma once

#include <windows.h>

#include "Api/ApiBackend.h"
#include "WinApi/AppRuntime/AppRuntime.h"
#include "WinApi/WindowHost/WindowHost.h"


namespace Blade::Backend {


class AppBackend : public Api::ApiBackend
{
public:
    AppBackend();

    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

    // auto createWindow() -> void override;

    auto process(const Api::BackendCommand& command) -> void override;

private:
    HINSTANCE m_hInstance;

    AppRuntime m_runtime;

    // TODO rename m_windowHost
    WindowHost m_windows;
};


} // namespace

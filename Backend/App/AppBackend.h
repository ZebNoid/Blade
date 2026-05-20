#pragma once

#include <windows.h>

#include "api.h"
#include "WinApi/WindowHost/WindowHost.h"
#include "Window/NativeWindow.h"


namespace Blade::Backend {


class AppBackend : public Api::ApiBackend
{
public:
    AppBackend();

    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

    auto createWindow() -> void override;

    auto createNativeWindow() -> NativeWindow*;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};

    WindowHost m_windows;
};


} // namespace

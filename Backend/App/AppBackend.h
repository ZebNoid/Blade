#pragma once

#include <windows.h>

#include "api.h"


namespace Blade::Backend {


class AppBackend : public Api::ApiBackend
{
public:
    AppBackend();

    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

    auto createWindow() -> void override;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};
};


} // namespace

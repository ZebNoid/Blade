#pragma once

#include <windows.h>

#include "ApiBackend.h"


namespace Blade::Backend {


class AppBackend : public ApiBackend
{
public:
    AppBackend();

    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};
};


} // namespace

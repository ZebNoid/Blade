#pragma once
#include "ApiBackend.h"


namespace Blade::Backend {


class AppBackend : public ApiBackend
{
public:
    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

private:
    HINSTANCE m_hInstance;
    MSG m_msg = {};
};


} // namespace

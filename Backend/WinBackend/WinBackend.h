#pragma once

#include "Api/ApiBackend.h"
#include "Context/WinAppContext.h"


namespace Blade::Backend {


class WinBackend : public ApiBackend
{
public:
    WinBackend();

    auto run() -> int override;

private:
    MSG m_msg = {};
};


} // namespace

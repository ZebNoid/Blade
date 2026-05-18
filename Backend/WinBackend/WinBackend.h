#pragma once

#include "Api/ApiBackend.h"
#include "Context/WinAppContext.h"


namespace Blade::Backend {


class WinBackend : public ApiBackend
{
public:
    WinBackend();

    auto run() -> int override;

    // auto context() -> WinAppContext&
    // {
    //     return m_appContext;
    // }

private:
    // WinAppContext m_appContext;

    MSG m_msg = {};
};


} // namespace

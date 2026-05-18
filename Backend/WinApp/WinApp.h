#pragma once

#include "Api/ApiAppBackend.h"
#include "Context/WinAppContext.h"


namespace Blade::Backend {


class WinApp : public ApiAppBackend
{
public:
    WinApp();

    auto run() -> int override;

    auto context() -> WinAppContext&
    {
        return m_appContext;
    }

private:
    WinAppContext m_appContext;

    MSG m_msg = {};
};


} // namespace

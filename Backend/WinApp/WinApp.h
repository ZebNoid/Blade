#pragma once

#include "Api/AppBackend.h"
#include "Context/WinAppContext.h"


namespace Blade::Backend {


class WinApp : public AppBackend
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

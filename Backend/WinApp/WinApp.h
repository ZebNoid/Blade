#pragma once

#include "Api/AppBackend.h"


namespace Blade::Backend {


class WinApp : public AppBackend
{
public:
    WinApp();

    auto run() -> int override;

private:
    MSG m_msg = {};
};


} // namespace

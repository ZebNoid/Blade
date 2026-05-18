#pragma once

#include "Api/AppBackend.h"


namespace Blade::Backend {


class NativeApp : public AppBackend
{
public:
    auto run() -> int override;

private:
    MSG m_msg = {};
};


} // namespace

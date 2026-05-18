#pragma once

#include "Api/AppBackend.h"


namespace Blade::Backend {


class NativeApp : public AppBackend
{
public:
    auto run() -> int;

private:
    MSG m_msg = {};
};


} // namespace

#pragma once

#include <windows.h>


namespace Blade::Backend {


class AppRuntime
{
public:
    auto run() -> int;

    auto quit(int code = 0) -> void;

private:
    MSG m_msg{};
};


} // namespace

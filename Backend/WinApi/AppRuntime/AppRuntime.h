#pragma once

#include <functional>

#include <windows.h>


namespace Blade::Backend {


class AppRuntime
{
public:
    using Tick = std::function<void()>;

    auto run(Tick tick = nullptr) -> int;

    auto quit(int code = 0) -> void;

private:
    MSG m_msg{};
};


} // namespace

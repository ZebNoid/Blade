#pragma once


namespace Blade::Backend {


class NativeApp
{
public:
    auto run() -> int;

private:
    MSG m_msg = {};
};


} // namespace

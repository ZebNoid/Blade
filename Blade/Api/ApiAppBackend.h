#pragma once

namespace Blade {


class ApiAppBackend
{
public:
    virtual ~ApiAppBackend() = default;

    virtual auto run() -> int = 0;
};


}

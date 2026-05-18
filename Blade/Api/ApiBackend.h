#pragma once

namespace Blade {


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto run() -> int = 0;
};


}

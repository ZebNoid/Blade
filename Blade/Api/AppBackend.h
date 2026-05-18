#pragma once

namespace Blade {


class AppBackend
{
public:
    virtual ~AppBackend() = default;

    virtual auto run() -> int = 0;
};


}

#pragma once
#include "BackendCommand.h"


namespace Blade::Api {


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto init() -> void = 0;

    virtual auto runApp() -> int = 0;

    virtual auto createWindow() -> void = 0;

    virtual auto quit() -> void = 0;

    virtual auto process(
        const Api::BackendCommand& command
    ) -> void = 0;
};


}

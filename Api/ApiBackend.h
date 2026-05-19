#pragma once

// #include "Windows/Window/Window.h"


namespace Blade {


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto init() -> void = 0;

    virtual auto runApp() -> int = 0;

    // virtual auto createWindow(Window& window) -> void = 0;

    virtual auto quit() -> void = 0;
};


}

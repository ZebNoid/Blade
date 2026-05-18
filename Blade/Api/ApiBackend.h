#pragma once
#include <complex.h>

#include "Windows/Window/Window.h"


namespace Blade {


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto runApp() -> int = 0;

    virtual auto createWindow(const Window& window) -> void = 0;
};


}

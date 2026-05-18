#pragma once
#include <complex.h>

#include "Windows/Window/Window.h"


namespace Blade {


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto run() -> int = 0;

    auto createWindow(const Window& window) -> void;
};


}

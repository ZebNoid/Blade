#pragma once

#include <windows.h>


namespace Blade {

// TODO Native App context
// struct AppContext
// {
//     HINSTANCE hInstance;
//     // config, settings, renderer, etc
// };

class AppContext
{
public:
    virtual ~AppContext() = default;
};

} // namespace

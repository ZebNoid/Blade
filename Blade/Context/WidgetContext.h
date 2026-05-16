#pragma once

#include "AppContext.h"


namespace Blade {


struct WidgetContext
{
    // TODO mve to native
    HWND hwnd = nullptr;
    AppContext* app = nullptr;
    // Window* window = nullptr;
    void* window = nullptr;
};


} // namespace

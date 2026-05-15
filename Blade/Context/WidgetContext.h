#pragma once

#include "AppContext.h"


struct WidgetContext
{
    HWND hwnd = nullptr;
    AppContext* app = nullptr;
    // Window* window = nullptr;
    void* window = nullptr;
};


#pragma once

#include <windows.h>

namespace Blade::Backend {

class ResourceManager;

struct NativeCreateContext
{
    HINSTANCE instance{};
    ResourceManager* resources = nullptr;
};

} // namespace Blade::Backend

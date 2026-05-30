#pragma once

#include <windows.h>

namespace Blade::Backend {

class ResourceManager;
class RenderRegistry;

struct NativeCreateContext
{
    HINSTANCE instance{};
    ResourceManager* resources = nullptr;
    RenderRegistry* renderNodes = nullptr;
};

} // namespace Blade::Backend

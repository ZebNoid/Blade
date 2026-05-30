#pragma once

namespace Blade::Backend {

class AppBackend;
class NativeWindow;

class WindowSurfaceRuntime
{
public:
    static auto Attach(AppBackend& backend, NativeWindow& window) -> void;
};

} // namespace Blade::Backend

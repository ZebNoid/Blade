#pragma once

#include <memory>
#include <windows.h>

#include "Window/NativeWindow.h"


namespace Blade::Backend {

// TODO rename WindowRuntime ?
class WindowHost
{
public:
    auto init(HINSTANCE hInstance) -> void;

    auto createWindow() -> NativeWindow*;

    auto destroyClosedWindows() -> void;

    auto windows() -> const auto&;

private:
    HINSTANCE m_hInstance = nullptr;

    std::vector<std::unique_ptr<NativeWindow>> m_windows;
};


} // namespace

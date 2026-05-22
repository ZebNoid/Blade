#pragma once

#include <memory>
#include <windows.h>

#include "WinApi/Window/NativeWindow.h"


namespace Blade::Backend {

// TODO rename WindowRuntime ?
class WindowHost
{
public:
    auto init(HINSTANCE hInstance) -> void;

    auto createWindow() -> std::unique_ptr<NativeWindow>;

    auto destroyClosedWindows() -> void;

    auto windows() -> const std::vector<std::unique_ptr<NativeWindow>>&;

    auto count() const -> size_t;

private:
    HINSTANCE m_hInstance = nullptr;

    std::vector<std::unique_ptr<NativeWindow>> m_windows;
};


} // namespace

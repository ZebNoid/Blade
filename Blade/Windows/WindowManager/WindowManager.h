#pragma once

#include <memory>
#include <vector>

#include "Windows/Window/Window.h"


namespace Blade {


class WindowManager
{
public:
    WindowManager() = default;

    auto bind(ApiBackend& backend) -> void;

    auto add(std::unique_ptr<Window> window) -> void;

    auto createWindow(Window& window) const -> void;

    auto destroyWindow(Window* target) -> void;

    auto createWindows() const -> void;

    auto empty() const -> bool;

private:
    ApiBackend* m_backend = nullptr;

    std::vector<std::unique_ptr<Window>> m_windows;
};


} // namespace

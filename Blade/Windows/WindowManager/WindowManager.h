#pragma once

#include <memory>
#include <vector>

#include "Windows/Window/Window.h"


namespace Blade {


class WindowManager
{
public:
    WindowManager() = default;

    auto add(std::unique_ptr<Window> window) -> void
    {
        m_windows.push_back(
            std::move(window)
        );
    }

    auto destroyWindow(Window* target) -> void;

    auto empty() const -> bool;

    auto bind(ApiBackend& backend) -> void
    {
        m_backend = &backend;
    }

    auto createWindows() -> void
    {
        // if (!m_backend) return;
        for (auto& window : m_windows)
        {
            m_backend->createWindow(*window);
            // createWindow(*window); // TODO
        }
    }

    auto createWindow(const Window& window) -> void
    {
        if (!m_backend) return;
        m_backend->createWindow(window);
    }

private:
    ApiBackend* m_backend = nullptr;

    std::vector<std::unique_ptr<Window>> m_windows;

    // friend class Window;
};


} // namespace

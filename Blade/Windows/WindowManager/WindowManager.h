#pragma once

#include <memory>
#include <vector>

#include "Windows/Window/Window.h"


namespace Blade {


class WindowManager
{
public:
    // WindowManager(AppContext& ctx);
    WindowManager()
    {
    }

    auto add(std::unique_ptr<Window> window) -> void
    {
        m_windows.push_back(
            std::move(window)
        );
    }

    auto destroyWindow(Window* target) -> void;

    auto empty() const -> bool;

    auto create(ApiBackend& backend) -> void
    {
        for (auto& window : m_windows)
        {
            backend.createWindow(*window);
        }
    }

    // auto create(const std::unique_ptr<ApiBackend>::element_type& backend) -> void
    // {
    //
    // }

private:
    // AppContext& m_appCtx;

    std::vector<std::unique_ptr<Window>> m_windows;

    friend class Window;
};


} // namespace

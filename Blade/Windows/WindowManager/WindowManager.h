#pragma once

#include <memory>
#include <vector>

#include "Windows/Window/Window.h"
#include "Windows/WindowBuilder/WindowBuilder.h"


namespace Blade {


class WindowManager
{
public:
    // WindowManager(AppContext& ctx);
    WindowManager() {}

    auto add(std::unique_ptr<Window> window) -> void
    {
        // m_windows.push_back(
        //   std::move(window)
        // );
    }

    auto createWindow(WindowBuilder&& builder) -> Window&;

    auto destroyWindow(Window* target) -> void;

    auto empty() const -> bool;

private:
    // AppContext& m_appCtx;

    std::vector<std::unique_ptr<Window>> m_windows;

    friend class Window;
};


} // namespace

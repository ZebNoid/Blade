#pragma once

#include <vector>
#include <memory>

#include "Windows/Window/Window.h"
#include "Windows/WindowBuilder/WindowBuilder.h"

class WindowManager
{
public:
    WindowManager(AppContext& ctx);

    auto createWindow(WindowBuilder&& builder) -> Window&;

    auto destroyWindow(Window* target) -> void;

    auto empty() const -> bool;

private:
    AppContext& m_appCtx;

    std::vector<std::unique_ptr<Window>> m_windows;

    friend class Window;
};

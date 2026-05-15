#pragma once

#include <vector>
#include <memory>

#include "../Window/Window.h"

class WindowManager
{
public:
    WindowManager(AppContext& ctx);

    auto newWindow(const std::string& title) -> Window&;

    auto destroyWindow(Window* target) -> void;

    auto empty() const -> bool;

private:
    AppContext& m_ctx;

    std::vector<std::unique_ptr<Window>> m_windows;
};


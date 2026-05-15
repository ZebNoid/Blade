#pragma once

#include <vector>
#include <memory>

#include "../Window/Window.h"

class WindowManager
{
public:
    WindowManager(AppContext& ctx);

    auto NewWindow(const std::string& title) -> Window&;

    auto DestroyWindow(Window* target) -> void;

    auto Empty() const -> bool;

private:
    AppContext& m_ctx;

    std::vector<std::unique_ptr<Window>> m_windows;
};


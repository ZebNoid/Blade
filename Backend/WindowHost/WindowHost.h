#pragma once

#include "WinApi/Window/NativeWindow.h"


namespace Blade::Backend {

class WindowHost
{
public:
    auto attach(NativeWindow* window) -> void;

    auto detach(NativeWindow* window) -> void;

    auto destroyClosedWindows() -> void;

    auto count() const -> size_t;

    auto windows() const -> const std::vector<NativeWindow*>&;

private:
    std::vector<NativeWindow*> m_windows;
};

} // namespace

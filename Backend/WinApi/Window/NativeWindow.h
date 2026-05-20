#pragma once

#include <windows.h>

#include "WinApi/MessageRouter/MessageRouter.h"


namespace Blade::Backend {


class NativeWindow
{
public:
    auto create(HINSTANCE hInstance) -> bool;

    auto show(int cmdShow = SW_SHOW) -> void;

    auto handle() const -> HWND;


    auto router() -> MessageRouter&;

    auto destroy() -> void;
    auto isAlive() const -> bool;

private:
    HWND m_hwnd = nullptr;
    bool m_alive = true;

    MessageRouter m_router;
};


} // namespace

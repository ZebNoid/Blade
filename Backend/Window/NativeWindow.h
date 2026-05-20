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

public:
    auto router() -> MessageRouter&;

private:
    HWND m_hwnd = nullptr;

    MessageRouter m_router;
};


} // namespace

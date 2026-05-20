#pragma once

#include <windows.h>


namespace Blade::Backend {


class NativeWindow
{
public:
    auto create(HINSTANCE hInstance) -> bool;

    auto show(int cmdShow = SW_SHOW) -> void;

    auto handle() const -> HWND;

private:
    HWND m_hwnd = nullptr;
};


} // namespace

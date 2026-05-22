#pragma once

#include <windows.h>


namespace Blade::Backend {


class NativeButton
{
public:
    auto create(HWND parent) -> bool;

    auto handle() const -> HWND;

private:
    HWND m_hwnd = nullptr;
};


} // namespace

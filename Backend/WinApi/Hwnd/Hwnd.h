#pragma once

#include <windows.h>

#include "Common/Common.h"


namespace Blade::Backend {


class Hwnd
{
public:
    struct HwndDesc
    {
        LPCWSTR className;
        LPCWSTR windowName;
        HWND parent = nullptr;
        DWORD exStyle = 0;
        DWORD style = 0;
        Api::Point position = {CW_USEDEFAULT, CW_USEDEFAULT};
        Api::Size size = {CW_USEDEFAULT,CW_USEDEFAULT};
        HMENU menu = nullptr;
        HINSTANCE hInstance = nullptr;
        LPVOID lpParam = nullptr;
    };

    static auto Create(const HwndDesc& desc) -> HWND;

    static auto Style() -> DWORD;

    static auto ExStyle() -> DWORD;
};


} // namespace

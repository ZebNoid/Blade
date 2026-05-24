#pragma once

#include <string>
#include <unordered_set>
#include <windows.h>

#include "WinApi/WindowProc/WindowProc.h"


namespace Blade::Backend {

using WndProc = LRESULT (CALLBACK*)(HWND, UINT, WPARAM, LPARAM);


class WindowClass
{
public:
    struct ClassDesc
    {
        WndProc proc = WindowProc;
        HBRUSH background = nullptr;
        HCURSOR cursor = nullptr;
        HICON icon = nullptr;
        UINT style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    };

public:
    static auto Init(HINSTANCE hInstance) -> void;

    static auto Get(const std::wstring& className) -> const wchar_t*;

    static auto Register(const std::wstring& className, const ClassDesc& desc) -> void;

private:
    static inline HINSTANCE m_hInstance = nullptr;
    static inline std::unordered_set<std::wstring> m_names;
};


} // namespace

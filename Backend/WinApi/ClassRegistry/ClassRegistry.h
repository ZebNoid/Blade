#pragma once

#include <string>
#include <unordered_map>
#include <windows.h>


namespace Blade::Backend {

using WndProc = LRESULT (CALLBACK*)(HWND, UINT, WPARAM, LPARAM);


class ClassRegistry
{
public:
    struct ClassDesc
    {
        std::wstring name;
        WndProc proc;
        HBRUSH background = nullptr;
        HCURSOR cursor = nullptr;
        HICON icon = nullptr;
        UINT style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    };

public:
    static auto Init(HINSTANCE hInstance) -> void;

    // TODO free

    static auto Get(const std::string& key) -> const wchar_t*;

    static auto Register(const std::string& key, const ClassDesc& desc) -> void;

private:
    static inline HINSTANCE m_hInstance = nullptr;
    static inline std::unordered_map<std::string, std::wstring> m_names;
};


} // namespace

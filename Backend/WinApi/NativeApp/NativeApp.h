#pragma once

#include <windows.h>


namespace Blade::Backend {


class NativeApp
{
public:
    NativeApp();

    static auto Get(HINSTANCE hInstance) -> HINSTANCE;

// private:
//     static inline HINSTANCE m_hInstance = nullptr;
private:
    static inline HINSTANCE m_hInstance = nullptr;
    // HINSTANCE m_hInstance;
    MSG m_msg = {};
};





} // namespace

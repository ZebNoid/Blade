#pragma once

#include <windows.h>
#include "../../Context/WidgetContext.h"
#include "../../Core/Core.h"
#include "../../Core/Encoding.h"
#include "../Utils/WinApiUtils.h"

class NativeWidget
{
protected:
#ifdef UNICODE
    using NativeString = std::wstring;
    using NativeChar = wchar_t;
#else
    using NativeString = std::string;
    using NativeChar = char;
#endif
    static auto toNativeString(const std::string& text) -> NativeString
    {
        return Utf8ToUtf16(text);
    }

public:
    virtual ~NativeWidget();

    auto Handle() const -> HWND;

protected:
    NativeWidget() = default;

    virtual auto Style() const -> DWORD;

    virtual auto ExStyle() const -> DWORD;

    virtual auto HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    virtual auto CreateNative(Rect rect) -> HWND = 0;

    auto ApplyFont(HFONT font) const -> void;

public:
    auto ClientSize() const -> Size
    {
        return m_size;
    }

protected:
    HWND m_hwnd = nullptr;
    WidgetContext m_ctx{};
    Size m_size{};
    WidgetId m_id{};

    static auto CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
};

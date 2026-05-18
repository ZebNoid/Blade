#pragma once

#include <windows.h>

#include "Backend/Utils/WinApiUtils.h"
#include "Context/WidgetContext.h"
#include "Core/Core.h"
#include "Core/Encoding.h"


namespace Blade::Backend {


class WinWidget
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
    virtual ~WinWidget();

    auto handle() const -> HWND;

protected:
    WinWidget() = default;

    virtual auto style() const -> DWORD;

    virtual auto exStyle() const -> DWORD;

    virtual auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    virtual auto widgetName() const -> std::string = 0;

    virtual auto createNative(Rect rect) -> HWND
    {
        if (m_ctx.hwnd == nullptr)
        {
            std::cerr << "[Error] " << widgetName() << "::create no parent HWND " << std::endl;
        }
        return nullptr;
    }

    auto applyFont(HFONT font) const -> void;

public:
    auto clientSize() const -> Size
    {
        return m_size;
    }

    virtual auto setRect(Rect rect) -> void;

    auto handle() -> HWND
    {
        return m_hwnd;
    }

protected:
    HWND m_hwnd = nullptr;
    WidgetContext m_ctx{};
    Size m_size{};
    WidgetId m_id{};

    static auto CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
};


} // namespace

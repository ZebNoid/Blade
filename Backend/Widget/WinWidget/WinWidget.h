#pragma once

#include <windows.h>

#include "Widgets/Widget/Widget.h"
#include "Api/ApiWidget.h"
#include "Core/Core.h"
#include "Core/Encoding.h"
#include "WidgetsProps/Common/Size.h"


namespace Blade::Backend {


class WinWidget : public ApiWidget
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
    // TODO ApiWidget!!
    ~WinWidget() override;

    // auto create(ApiWidget& parent) -> void override;

    auto setRect(const Rect& rect) -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    // TODO other
    auto handle() const -> HWND;

protected:

    virtual auto style() const -> DWORD;

    virtual auto exStyle() const -> DWORD;

    virtual auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    virtual auto createNative(Rect rect, HWND parent = nullptr) -> HWND
    {
        std::cerr << "[Error] " << name() << "::create not defined " << std::endl;
        return nullptr;
    }

    auto applyFont(HFONT font) const -> void;

public:
    auto clientSize() const -> Size
    {
        return m_size;
    }

    auto handle() -> HWND
    {
        return m_hwnd;
    }

protected:
    HWND m_hwnd = nullptr;
    Size m_size{};
    WidgetId m_id{};

    static auto CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
};


} // namespace

#pragma once

#include <windows.h>

#include "Api/ApiWidget.h"
#include "Core/Core.h"
#include "WidgetsProps/Common/Size.h"


namespace Blade::Backend {


class WinWidget : public ApiWidget
{
public:
    ~WinWidget() override;

    auto setRect(const Rect& rect) -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    auto handle() const -> HWND; // TODO other

protected:
    virtual auto style() const -> DWORD;

    virtual auto exStyle() const -> DWORD;

    virtual auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    virtual auto createNative(Rect rect) -> HWND
    {
        return nullptr;
    }

    auto applyFont(HFONT font) const -> void;

    auto parentHandle() const -> HWND
    {
        const auto parent = dynamic_cast<WinWidget*>(m_parent);
        return parent->handle();
    }

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

#pragma once

#include "Context/WidgetContext.h"
#include "Widget/WinRender/WinRender.h"
#include "Widget/WinWidget/WinWidget.h"


namespace Blade::Backend {


class WinCustom : public WinWidget
{
public:
    WinCustom() = default;

    auto create(WidgetId id) -> void;

protected:
    auto style() const -> DWORD override;

    auto exStyle() const -> DWORD override;

    auto createNative(Rect rect, HWND parent = nullptr) -> HWND override;

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

    virtual auto paint(HDC hdc, RECT rect) -> void = 0;

protected:
    WinRender m_render;
    HFONT m_systemFont = nullptr;
};

} // namespace

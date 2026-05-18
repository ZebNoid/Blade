#pragma once

#include "Backend/NativeRender/NativeRender.h"
#include "Context/WidgetContext.h"
#include "Widget/WinWidget/WinWidget.h"


namespace Blade::Backend {


class WinCustom : public WinWidget
{
public:
    WinCustom() = default;

    auto create(const WidgetContext& ctx, WidgetId id) -> void;

protected:
    auto style() const -> DWORD override;

    auto exStyle() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

    virtual auto paint(HDC hdc, RECT rect) -> void = 0;

protected:
    Backend::NativeRender m_render;
    HFONT m_systemFont = nullptr;
};

} // namespace

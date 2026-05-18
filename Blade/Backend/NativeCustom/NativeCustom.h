#pragma once

#include "Backend/NativeRender/NativeRender.h"
#include "Backend/NativeWidget/NativeWidget.h"
#include "Context/WidgetContext.h"


namespace Blade {


class NativeCustom : public NativeWidget
{
public:
    NativeCustom() = default;

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

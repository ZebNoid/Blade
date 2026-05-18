#pragma once
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

    auto widgetName() const -> std::string override { return "NativeCustom"; }

    auto createNative(Rect rect) -> HWND override;

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

private:
    // HFONT m_font = nullptr;
};

} // namespace

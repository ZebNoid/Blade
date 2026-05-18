#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "WidgetsProps/Widget/LabelProps.h"


namespace Blade {


class NativeLabel : public NativeCustom
{
public:
    NativeLabel() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const LabelProps& props, const std::string& text) -> void;

protected:
    // auto style() const -> DWORD override;
    //
    // auto exStyle() const -> DWORD override;

    auto widgetName() const -> std::string override { return "NativeLabel"; }

    auto paint(HDC hdc, RECT rect) -> void override;

    // auto createNative(Rect rect) -> HWND override;
    //
    // auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

private:
    LabelProps m_props{};
    std::wstring m_text;
    HFONT m_font = nullptr;
};


} // namespace

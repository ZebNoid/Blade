#pragma once

#include "Widget/WinCustom/WinCustom.h"
#include "Widget/WinWidget/WinWidget.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsProps/Widget/LabelProps.h"


namespace Blade::Backend {


class WinLabel : public WinCustom
{
public:
    explicit WinLabel(Widget& widget); // TODO in ApiWidget
    auto create(ApiWidget& parent) -> void override;

    auto create(WidgetId id, const LabelProps& props, const std::wstring& text) -> void;

protected:
    // auto style() const -> DWORD override;
    //
    // auto exStyle() const -> DWORD override;

    auto name() const -> std::string override { return "WinLabel"; }

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

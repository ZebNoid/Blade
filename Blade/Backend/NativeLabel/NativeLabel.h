#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "Props/Widget/LabelProps.h"


namespace Blade {


class NativeLabel : public NativeWidget
{
public:
    NativeLabel() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const LabelProps& props, const std::string& text) -> void;

protected:
    auto style() const -> DWORD override;

    auto widgetName() const -> std::string override { return "NativeLabel"; }

    auto createNative(Rect rect) -> HWND override;

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

private:
    std::string m_text;
    HFONT m_font = nullptr;
    LabelProps m_props{};

public:
    auto setRect(Rect rect) -> void;
};


} // namespace

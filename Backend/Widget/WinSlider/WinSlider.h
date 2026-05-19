#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/SliderProps.h"


namespace Blade::Backend {


class WinSlider : public WinWidget
{

public:
    WinSlider() = default;

    auto create(WidgetId id, const SliderProps& props, const int value) -> void;

protected:
    auto name() const -> std::string override { return "WinSlider"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    SliderProps m_props{};
    int m_value;
};


} // namespace

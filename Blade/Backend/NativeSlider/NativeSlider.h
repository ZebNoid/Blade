#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "WidgetsProps/Widget/SliderProps.h"


namespace Blade {


class NativeSlider : public NativeWidget
{

public:
    NativeSlider() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const SliderProps& props, const int value) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeSlider"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    SliderProps m_props{};
    int m_value;
};


} // namespace

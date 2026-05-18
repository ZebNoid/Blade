#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "WidgetsProps/Widget/RadioButtonProps.h"


namespace Blade {


class NativeRadioButton : public NativeWidget
{

public:
    NativeRadioButton() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const RadioButtonProps& props, const std::string& string) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeRadioButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    RadioButtonProps m_props{};
    std::string m_text;
};


} // namespace

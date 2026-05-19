#pragma once

#include "Widget/WinWidget/ApiWidget.h"
#include "WidgetsProps/Widget/RadioButtonProps.h"


namespace Blade::Backend {


class WinRadioButton : public ApiWidget
{

public:
    WinRadioButton() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const RadioButtonProps& props, const std::string& string) -> void;

protected:
    auto widgetName() const -> std::string override { return "WinRadioButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    RadioButtonProps m_props{};
    std::string m_text;
};


} // namespace

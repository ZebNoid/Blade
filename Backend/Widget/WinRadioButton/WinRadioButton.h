#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/RadioButtonProps.h"


namespace Blade::Backend {


class WinRadioButton : public WinWidget
{

public:
    WinRadioButton() = default;

    auto create(WidgetId id, const RadioButtonProps& props, const std::string& string) -> void;

protected:
    auto name() const -> std::string override { return "WinRadioButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect, HWND parent = nullptr) -> HWND override;

private:
    RadioButtonProps m_props{};
    std::string m_text;
};


} // namespace

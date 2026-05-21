#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/RadioButtonProps.h"


namespace Blade::Backend {


class WinRadioButton : public WinWidget
{

public:
    WinRadioButton() = default;

    auto create(WidgetId id, const RadioButtonProps& props, const std::wstring& string) -> void;

    auto name() const -> std::string override { return "WinRadioButton"; }

protected:
    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    RadioButtonProps m_props{};
    std::wstring m_text;
};


} // namespace

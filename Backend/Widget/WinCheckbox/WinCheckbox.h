#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/CheckboxProps.h"


namespace Blade::Backend {


class WinCheckbox : public WinWidget
{

public:
    WinCheckbox() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const CheckboxProps& props, const std::string& string) -> void;

protected:
    auto widgetName() const -> std::string override { return "WinCheckbox"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    CheckboxProps m_props{};
    std::string m_text;
};


} // namespace

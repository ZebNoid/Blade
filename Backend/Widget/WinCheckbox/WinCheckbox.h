#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/CheckboxProps.h"


namespace Blade::Backend {


class WinCheckbox : public WinWidget
{

public:
    WinCheckbox() = default;

    auto create(WidgetId id, const CheckboxProps& props, const std::wstring& string) -> void;

    auto name() const -> std::string override { return "WinCheckbox"; }

protected:
    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    CheckboxProps m_props{};
    std::wstring m_text;
};


} // namespace

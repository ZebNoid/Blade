#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "Props/Widget/CheckboxProps.h"


namespace Blade {


class NativeCheckbox : public NativeWidget
{

public:
    NativeCheckbox() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const CheckboxProps& props, const std::string& string) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeCheckbox"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    CheckboxProps m_props{};
    std::string m_text;

public:
    auto setRect(Rect rect) const -> void;
};


} // namespace

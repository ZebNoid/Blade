#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsEvents/Widget/ButtonEvents.h"
#include "WidgetsProps/Widget/ButtonProps.h"


namespace Blade::Backend {


class WinButton : public WinWidget
{
public:
    WinButton() = default;

    auto create(
        const WidgetContext& ctx,
        WidgetId id,
        const ButtonProps& props,
        const std::string& text
    ) -> void;

protected:
    auto widgetName() const -> std::string override { return "WinButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect, HWND parent = nullptr) -> HWND override;

private:
    ButtonProps m_props{};
    ButtonEvents m_callbacks{};
    std::string m_text;
};


} // namespace

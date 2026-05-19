#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsEvents/Widget/ButtonEvents.h"
#include "WidgetsProps/Widget/ButtonProps.h"


namespace Blade::Backend {


class WinButton : public WinWidget
{
public:
    WinButton() = default;

    explicit WinButton(Widget& widget); // TODO in ApiWidget

    auto create(ApiWidget& parent) -> void override;

    auto create(
        WidgetId id,
        const ButtonProps& props,
        const std::wstring& text
    ) -> void;

protected:
    auto name() const -> std::string override { return "WinButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    ButtonProps m_props{};
    ButtonEvents m_callbacks{};
    std::wstring m_text;
};


} // namespace

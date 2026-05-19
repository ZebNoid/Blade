#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/TextFieldProps.h"
#include "Widgets/TextField/TextField.h"


namespace Blade::Backend {


class WinTextField : public WinWidget
{
public:
    WinTextField() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const TextFieldProps& props, const std::string& text) -> void;

protected:
    auto widgetName() const -> std::string override { return "WinTextField"; }

    auto style() const -> DWORD override;

    auto exStyle() const -> DWORD override;

    auto createNative(Rect rect, HWND parent = nullptr) -> HWND override;

    auto setPlaceholder() -> void;

public:
    auto setRect(const Rect& rect) -> void override;

private:
    TextFieldProps m_props{};
    // TODO remove? store text in Widget?
    std::string m_text;
};


} // namespace

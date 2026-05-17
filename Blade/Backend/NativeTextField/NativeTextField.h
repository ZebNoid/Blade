#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "Props/Widget/TextFieldProps.h"
#include "Widgets/TextField/TextField.h"


namespace Blade {


class NativeTextField : public NativeWidget
{
public:
    NativeTextField() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const TextFieldProps& props, const std::string& text) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeTextField"; }

    auto style() const -> DWORD override;

    auto exStyle() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

    auto setPlaceholder() -> void;

public:
    auto setRect(Rect rect) -> void override;

private:
    TextFieldProps m_props{};
    // TODO remove? store text in Widget?
    std::string m_text;
};


} // namespace

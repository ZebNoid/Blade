#pragma once

// #include <windows.h>

#include "WidgetsEvents/Widget/ButtonEvents.h"
#include "WidgetsProps/Widget/ButtonProps.h"


namespace Blade {


struct WidgetContext;
class NativeWidget;
class Button;


class NativeButton : public NativeWidget
{
public:
    NativeButton() = default;

    auto create(
        const WidgetContext& ctx,
        WidgetId id,
        const ButtonProps& props,
        const std::string& text
    ) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    ButtonProps m_props{};
    ButtonEvents m_callbacks{};
    std::string m_text;
};


} // namespace

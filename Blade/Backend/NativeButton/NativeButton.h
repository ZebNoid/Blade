#pragma once

// #include <windows.h>

#include "WidgetsProps/Widget/ButtonProps.h"


namespace Blade {


struct WidgetContext;
class NativeWidget;
class Button;


class NativeButton : public NativeWidget
{
public:
    NativeButton() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const ButtonProps& props, const std::string& string) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeButton"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;


private:
    ButtonProps m_props{};
    std::string m_text;
};


} // namespace

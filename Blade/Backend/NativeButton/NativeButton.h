#pragma once

// #include <windows.h>

namespace Blade {


struct WidgetContext;
class NativeWidget;
class Button;


class NativeButton : public NativeWidget
{
public:
    NativeButton() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const std::string& text) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeButton"; }

    auto createNative(Rect rect) -> HWND override;

private:
    std::string m_text;

public:
    auto setRect(Rect rect) -> void;
};


} // namespace

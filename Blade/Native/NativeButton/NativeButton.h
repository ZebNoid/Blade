#pragma once

// #include <windows.h>

struct WidgetContext;
class NativeWidget;
class Button;

class NativeButton : public NativeWidget
{
public:
    NativeButton() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const std::string& text) -> void;

protected:
    auto createNative(Rect rect) -> HWND override;

private:
    std::string m_text;

public:
    auto setRect(Rect rect) -> void;
};

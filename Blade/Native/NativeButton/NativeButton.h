#pragma once

// #include <windows.h>

struct WidgetContext;
class NativeWidget;
class Button;

class NativeButton : public NativeWidget
{
public:
    NativeButton() = default;

    auto Create(const WidgetContext& ctx, WidgetId id, const std::string& text) -> void;

protected:
    auto CreateNative(Rect rect) -> HWND override;

private:
    std::string m_text;

public:
    auto SetRect(Rect rect) -> void;
};

#pragma once

#include "../NativeWidget/NativeWidget.h"


class NativeTextField : public NativeWidget
{
public:
    NativeTextField() = default;

    auto Create(const WidgetContext& ctx, WidgetId id) -> void;

protected:
    auto CreateNative(Rect rect) -> HWND override;

private:


public:
    auto SetRect(Rect rect) -> void;
};

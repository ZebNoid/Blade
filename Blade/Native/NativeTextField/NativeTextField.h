#pragma once

#include "../NativeWidget/NativeWidget.h"


class NativeTextField : public NativeWidget
{
public:
    NativeTextField() = default;

    auto create(const WidgetContext& ctx, WidgetId id) -> void;

protected:
    auto createNative(Rect rect) -> HWND override;

private:


public:
    auto setRect(Rect rect) -> void;
};

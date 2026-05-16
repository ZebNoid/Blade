#pragma once

#include "Backend/NativeWidget/NativeWidget.h"


namespace Blade {


class NativeTextField : public NativeWidget
{
public:
    NativeTextField() = default;

    auto create(const WidgetContext& ctx, WidgetId id) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeTextField"; }

    auto createNative(Rect rect) -> HWND override;

private:


public:
    auto setRect(Rect rect) -> void;
};


} // namespace

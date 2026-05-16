#pragma once

#include "Backend/NativeWidget/NativeWidget.h"


namespace Blade {


class NativeRadioButton : public NativeWidget
{

public:
    NativeRadioButton() = default;

    auto create(const WidgetContext& ctx, const WidgetId id, const std::string& text) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeRadioButton"; }

    auto createNative(Rect rect) -> HWND override;

private:
    std::string m_text;

public:
    auto setRect(Rect rect) const -> void;
};


} // namespace

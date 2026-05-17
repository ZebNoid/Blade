#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "WidgetsProps/Widget/ProgressProps.h"

namespace Blade {


class NativeProgress : public NativeWidget
{

public:
    NativeProgress() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const ProgressProps& props, const int value) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeProgress"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    ProgressProps m_props{};
    int m_value;
};



} // namespace

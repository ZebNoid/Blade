#pragma once

#include "Context/WidgetContext.h"
#include "Widget/WinWidget/ApiWidget.h"
#include "WidgetsProps/Widget/ProgressProps.h"

namespace Blade::Backend {


class WinProgress : public ApiWidget
{

public:
    WinProgress() = default;

    auto create(const WidgetContext& ctx, WidgetId id, const ProgressProps& props, const int value) -> void;

protected:
    auto widgetName() const -> std::string override { return "WinProgress"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    ProgressProps m_props{};
    int m_value;
};



} // namespace

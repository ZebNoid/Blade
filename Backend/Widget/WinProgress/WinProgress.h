#pragma once

#include "Context/WidgetContext.h"
#include "Widget/WinWidget/WinWidget.h"
#include "WidgetsProps/Widget/ProgressProps.h"

namespace Blade::Backend {


class WinProgress : public WinWidget
{

public:
    WinProgress() = default;

    auto create(WidgetId id, const ProgressProps& props, const int value) -> void;

protected:
    auto name() const -> std::string override { return "WinProgress"; }

    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

private:
    ProgressProps m_props{};
    int m_value;
};



} // namespace

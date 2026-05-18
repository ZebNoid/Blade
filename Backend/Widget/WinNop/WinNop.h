#pragma once
#include "Widget/WinCustom/WinCustom.h"
#include "WidgetsProps/Widget/NopProps.h"


namespace Blade::Backend {


class WinNop : public WinCustom
{
public:
    auto create(const WidgetContext& ctx, WidgetId id, const NopProps& props, const std::string& text) -> void;

protected:
    auto widgetName() const -> std::string override { return "WinNop"; }

    auto paint(HDC hdc, RECT rect) -> void override;

private:
    NopProps m_props{};
    std::wstring m_text;
};


} // namespace

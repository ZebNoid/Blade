#pragma once
#include "Backend/NativeCustom/NativeCustom.h"
#include "WidgetsProps/Widget/NopProps.h"


namespace Blade {


class NativeNop : public NativeCustom
{
public:
    auto create(const WidgetContext& ctx, WidgetId id, const NopProps& props, const std::string& text) -> void;

protected:
    auto widgetName() const -> std::string override { return "NativeNop"; }

    auto paint(HDC hdc, RECT rect) -> void override;

private:
    NopProps m_props{};
    std::wstring m_text;
};


} // namespace

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

private:
    NopProps m_props{};
    std::string m_text;
};


} // namespace

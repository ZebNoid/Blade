#pragma once
#include "Widget/WinCustom/WinCustom.h"
#include "WidgetsProps/Widget/NopProps.h"
#include "Windows/Window/Window.h"


namespace Blade::Backend {


class WinNop : public WinCustom
{
public:
    explicit WinNop(const std::wstring& text);

    // TODO in ApiWidget
    explicit WinNop(Widget& widget);

    auto create(ApiWidget& parent) -> void override;

    auto name() const -> std::string override { return "WinNop"; }

    auto create(WidgetId id, const NopProps& props, const std::wstring& text) -> void;

protected:
    auto paint(HDC hdc, RECT rect) -> void override;

private:
    NopProps m_props{};
    std::wstring m_text = L"Nop";
};


} // namespace

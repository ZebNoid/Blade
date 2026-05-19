#pragma once
#include "Widget/WinCustom/WinCustom.h"
#include "WidgetsProps/Widget/NopProps.h"
#include "Windows/Window/Window.h"


namespace Blade::Backend {


class WinNop : public WinCustom
{
public:
    explicit WinNop(const std::wstring& text);
    explicit WinNop(Widget& widget); // TODO in ApiWidget
    auto create(ApiWidget& parent) -> void override;

    auto create(WidgetId id, const NopProps& props, const std::wstring& text) -> void;

    auto name() const -> std::string override { return "WinNop"; }

protected:
    auto paint(HDC hdc, RECT rect) -> void override;

private:
    NopProps m_props{};
    std::wstring m_text = L"Nop";
};


} // namespace

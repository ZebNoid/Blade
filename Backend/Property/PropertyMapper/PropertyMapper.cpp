#include "PropertyMapper.h"

#include "Common/Logger.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

namespace {

template <typename T, typename Apply>
auto ApplyValue(const Api::PropertyValue& value, Apply apply) -> void
{
    if (const auto* typed = std::get_if<T>(&value)) apply(*typed);
}

} // namespace

auto PropertyMapper::Apply(HWND hwnd, const Api::PropertyMap& props) -> void
{
    for (const auto& [key, value] : props)
    {
        switch (key)
        {
        case Api::Props::Rect:
            ApplyValue<Api::Rect>(value, [hwnd](const auto& rect) { HwndApi::SetRect(hwnd, rect); });
            break;

        case Api::Props::Title:
            ApplyValue<Api::Text>(value, [hwnd](const auto& text) { HwndApi::SetTitle(hwnd, text); });
            break;

        case Api::Props::Size:
            ApplyValue<Api::Size>(value, [hwnd](const auto& size) { HwndApi::SetSize(hwnd, size); });
            break;

        case Api::Props::Position:
            ApplyValue<Api::Point>(value, [hwnd](const auto& point) { HwndApi::SetPosition(hwnd, point); });
            break;

        case Api::Props::Visible:
            ApplyValue<bool>(value, [hwnd](bool visible) { HwndApi::SetVisible(hwnd, visible); });
            break;

        case Api::Props::IsDefault:
        case Api::Props::ContextMenus:
        case Api::Props::MenuTrigger:
        case Api::Props::Shortcut:
        case Api::Props::DropTarget:
            break;

        default:
            LOGF_W(L" -> ApplyProps::%s not implemented", to_string(key).c_str());
        }
    }
}

} // namespace Blade::Backend

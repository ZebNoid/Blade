#include "NativeWindowProps.h"

#include "Common/Logger.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

namespace {

auto SetStyleFlag(DWORD& style, DWORD flag, bool enabled) -> void
{
    if (enabled)
    {
        style |= flag;
    }
    else
    {
        style &= ~flag;
    }
}

auto ApplyCaptionButtons(HWND hwnd, Api::CaptionButton buttons) -> void
{
    auto* systemMenu = GetSystemMenu(hwnd, FALSE);

    if (!systemMenu)
    {
        return;
    }

    EnableMenuItem(
        systemMenu,
        SC_CLOSE,
        MF_BYCOMMAND | (Api::Has(buttons, Api::CaptionButton::Close) ? MF_ENABLED : MF_GRAYED)
    );
}

auto ApplyCaption(HWND hwnd, const Api::CaptionProps& caption) -> void
{
    auto style = static_cast<DWORD>(GetWindowLongPtr(hwnd, GWL_STYLE));

    SetStyleFlag(style, WS_CAPTION, caption.visible);
    SetStyleFlag(style, WS_MINIMIZEBOX, Api::Has(caption.buttons, Api::CaptionButton::Min));
    SetStyleFlag(style, WS_MAXIMIZEBOX, Api::Has(caption.buttons, Api::CaptionButton::Max));

    SetWindowLongPtr(hwnd, GWL_STYLE, static_cast<LONG_PTR>(style));
    ApplyCaptionButtons(hwnd, caption.buttons);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

} // namespace

auto NativeWindowProps::Apply(HWND hwnd, const Api::PropertyMap& propertyMap) -> Api::PropertyMap
{
    Api::PropertyMap nativeProps;

    for (const auto& [key, value] : propertyMap)
    {
        switch (key)
        {
        case Api::Props::Rect:
            if (const auto* rect = std::get_if<Api::Rect>(&value))
            {
                LOGF_D(L" -> Apply::%s %s", to_string(key).c_str(), to_string(*rect).c_str());
                NativeApi::SetClientRect(hwnd, *rect);
            }
            break;

        case Api::Props::Size:
            if (const auto* size = std::get_if<Api::Size>(&value))
            {
                LOGF_D(L" -> Apply::%s %s", to_string(key).c_str(), to_string(*size).c_str());
                NativeApi::SetClientSize(hwnd, *size);
            }
            break;

        case Api::Props::Caption:
            if (const auto* caption = std::get_if<Api::CaptionProps>(&value))
            {
                ApplyCaption(hwnd, *caption);
            }
            break;

        default:
            nativeProps[key] = value;
            break;
        }
    }

    return nativeProps;
}

} // namespace Blade::Backend

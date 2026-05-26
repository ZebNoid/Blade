#include "NativeWindowProps.h"

#include "Common/Logger.h"
#include "NativeWindowApi/NativeWindowApi.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

auto NativeWindowProps::Apply(HWND hwnd, const Api::PropertyMap& propertyMap) -> Api::PropertyMap
{
    Api::PropertyMap nativeProps;
    const Api::WindowPlacementProps* placement = nullptr;
    const Api::WindowState* state = nullptr;

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
                NativeWindowApi::SetCaption(hwnd, *caption);
            }
            break;

        case Api::Props::Placement:
            placement = std::get_if<Api::WindowPlacementProps>(&value);
            break;

        case Api::Props::Resizable:
            if (const auto* resizable = std::get_if<bool>(&value))
            {
                NativeWindowApi::SetResizable(hwnd, *resizable);
            }
            break;

        case Api::Props::TopMost:
            if (const auto* topMost = std::get_if<bool>(&value))
            {
                NativeWindowApi::SetTopMost(hwnd, *topMost);
            }
            break;

        case Api::Props::Taskbar:
            if (const auto* taskbar = std::get_if<bool>(&value))
            {
                NativeWindowApi::SetTaskbar(hwnd, *taskbar);
            }
            break;

        case Api::Props::State:
            state = std::get_if<Api::WindowState>(&value);
            break;

        default:
            nativeProps[key] = value;
            break;
        }
    }

    if (placement)
    {
        NativeWindowApi::SetPlacement(hwnd, *placement);
        nativeProps.erase(Api::Props::Position);
    }

    if (state)
    {
        NativeWindowApi::SetState(hwnd, *state);
    }

    return nativeProps;
}

} // namespace Blade::Backend

#include "NativeWindowProps.h"

#include "Components/Window/NativeWindow.h"
#include "Common/Logger.h"
#include "NativeWindowApi/NativeWindowApi.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

auto NativeWindowProps::Apply(NativeWindow& window, const Api::PropertyMap& propertyMap) -> Api::PropertyMap
{
    Api::PropertyMap nativeProps;
    const auto hwnd = window.handle();
    const Api::Rect* rect = nullptr;
    const Api::Size* size = nullptr;
    const Api::CaptionProps* caption = nullptr;
    const Api::WindowPlacementProps* placement = nullptr;
    const bool* resizable = nullptr;
    const bool* topMost = nullptr;
    const bool* taskbar = nullptr;
    const bool* visible = nullptr;
    const Api::Size* minSize = nullptr;
    const Api::Size* maxSize = nullptr;
    const Api::WindowState* state = nullptr;

    // TODO prop order WindowState must be latest
    for (const auto& [key, value] : propertyMap)
    {
        switch (key)
        {
        case Api::Props::Rect:
            rect = std::get_if<Api::Rect>(&value);
            break;

        case Api::Props::Size:
            size = std::get_if<Api::Size>(&value);
            break;

        case Api::Props::Caption:
            caption = std::get_if<Api::CaptionProps>(&value);
            break;

        case Api::Props::Placement:
            placement = std::get_if<Api::WindowPlacementProps>(&value);
            break;

        case Api::Props::Resizable:
            resizable = std::get_if<bool>(&value);
            break;

        case Api::Props::TopMost:
            topMost = std::get_if<bool>(&value);
            break;

        case Api::Props::Taskbar:
            taskbar = std::get_if<bool>(&value);
            break;

        case Api::Props::Visible:
            visible = std::get_if<bool>(&value);
            break;

        case Api::Props::MinSize:
            minSize = std::get_if<Api::Size>(&value);
            break;

        case Api::Props::MaxSize:
            maxSize = std::get_if<Api::Size>(&value);
            break;

        case Api::Props::State:
            state = std::get_if<Api::WindowState>(&value);
            break;

        default:
            nativeProps[key] = value;
            break;
        }
    }

    if (caption) NativeWindowApi::SetCaption(hwnd, *caption);
    if (resizable) NativeWindowApi::SetResizable(hwnd, *resizable);
    if (taskbar) NativeWindowApi::SetTaskbar(hwnd, *taskbar);
    if (topMost) NativeWindowApi::SetTopMost(hwnd, *topMost);
    if (minSize) window.setMinSize(*minSize);
    if (maxSize) window.setMaxSize(*maxSize);
    if (visible) NativeApi::SetVisible(hwnd, *visible);

    if (rect)
    {
        LOGF_D(L" -> Apply::%s %s", to_string(Api::Props::Rect).c_str(), to_string(*rect).c_str());
        if (state && *state != Api::WindowState::Normal)
        {
            NativeWindowApi::SetNormalRect(hwnd, {rect->position(), NativeApi::ClientToWindowSize(hwnd, rect->size())});
        }
        else
        {
            NativeApi::SetClientRect(hwnd, *rect);
        }
    }
    else if (size)
    {
        LOGF_D(L" -> Apply::%s %s", to_string(Api::Props::Size).c_str(), to_string(*size).c_str());
        if (!(state && *state != Api::WindowState::Normal))
        {
            NativeApi::SetClientSize(hwnd, *size);
        }
    }

    if (placement)
    {
        if (state && *state != Api::WindowState::Normal && size)
        {
            NativeWindowApi::SetNormalPlacement(hwnd, *placement, NativeApi::ClientToWindowSize(hwnd, *size));
        }
        else
        {
            NativeWindowApi::SetPlacement(hwnd, *placement);
        }

        nativeProps.erase(Api::Props::Position);
    }

    if (state)
    {
        NativeWindowApi::SetState(hwnd, *state);
    }

    return nativeProps;
}

} // namespace Blade::Backend

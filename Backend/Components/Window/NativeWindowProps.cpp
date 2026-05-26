#include "NativeWindowProps.h"

#include "Components/Window/NativeWindow.h"
#include "Common/Logger.h"
#include "NativeWindowApi/NativeWindowApi.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

namespace {

template <typename T>
auto Get(const Api::PropertyMap& propertyMap, Api::Props prop) -> const T*
{
    const auto it = propertyMap.find(prop);
    return it == propertyMap.end() ? nullptr : std::get_if<T>(&it->second);
}

auto RemoveWindowProps(Api::PropertyMap& propertyMap) -> void
{
    propertyMap.erase(Api::Props::Rect);
    propertyMap.erase(Api::Props::Size);
    propertyMap.erase(Api::Props::Caption);
    propertyMap.erase(Api::Props::Placement);
    propertyMap.erase(Api::Props::Resizable);
    propertyMap.erase(Api::Props::TopMost);
    propertyMap.erase(Api::Props::Taskbar);
    propertyMap.erase(Api::Props::Visible);
    propertyMap.erase(Api::Props::MinSize);
    propertyMap.erase(Api::Props::MaxSize);
    propertyMap.erase(Api::Props::State);
}

} // namespace

auto NativeWindowProps::Apply(NativeWindow& window, const Api::PropertyMap& propertyMap) -> Api::PropertyMap
{
    Api::PropertyMap nativeProps = propertyMap;
    RemoveWindowProps(nativeProps);

    const auto hwnd = window.handle();
    const auto* rect = Get<Api::Rect>(propertyMap, Api::Props::Rect);
    const auto* size = Get<Api::Size>(propertyMap, Api::Props::Size);
    const auto* caption = Get<Api::CaptionProps>(propertyMap, Api::Props::Caption);
    const auto* placement = Get<Api::WindowPlacementProps>(propertyMap, Api::Props::Placement);
    const auto* resizable = Get<bool>(propertyMap, Api::Props::Resizable);
    const auto* topMost = Get<bool>(propertyMap, Api::Props::TopMost);
    const auto* taskbar = Get<bool>(propertyMap, Api::Props::Taskbar);
    const auto* visible = Get<bool>(propertyMap, Api::Props::Visible);
    const auto* minSize = Get<Api::Size>(propertyMap, Api::Props::MinSize);
    const auto* maxSize = Get<Api::Size>(propertyMap, Api::Props::MaxSize);
    const auto* state = Get<Api::WindowState>(propertyMap, Api::Props::State);

    if (caption) NativeWindowApi::SetCaption(hwnd, *caption);
    if (resizable) NativeWindowApi::SetResizable(hwnd, *resizable);
    if (taskbar) NativeWindowApi::SetTaskbar(hwnd, *taskbar);
    if (topMost) NativeWindowApi::SetTopMost(hwnd, *topMost);
    if (minSize) window.setMinSize(*minSize);
    if (maxSize) window.setMaxSize(*maxSize);

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

    if (visible && !*visible)
    {
        NativeApi::SetVisible(hwnd, false);
    }
    else if (state)
    {
        NativeWindowApi::SetState(hwnd, *state);
    }
    else if (visible)
    {
        NativeApi::SetVisible(hwnd, true);
    }

    return nativeProps;
}

} // namespace Blade::Backend

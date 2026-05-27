#include "NativeWindowProps.h"

#include "Components/Window/NativeWindow.h"
#include "Common/Logger.h"
#include "NativeWindowApi/NativeWindowApi.h"
#include "NativeWindowStyle/NativeWindowStyle.h"
#include "Property/PropertyReader.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

namespace {

struct Props
{
    const Api::Text* icon{};
    const Api::Rect* rect{};
    const Api::Size* size{};
    const Api::CaptionProps* caption{};
    const Api::WindowPlacementProps* placement{};
    const bool* resizable{};
    const bool* topMost{};
    const bool* taskbar{};
    const bool* visible{};
    const Api::Size* minSize{};
    const Api::Size* maxSize{};
    const Api::WindowState* state{};
};

auto GetProps(const Api::PropertyMap& propertyMap) -> Props
{
    return {
        .icon = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Icon),
        .rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect),
        .size = PropertyReader::Get<Api::Size>(propertyMap, Api::Props::Size),
        .caption = PropertyReader::Get<Api::CaptionProps>(propertyMap, Api::Props::Caption),
        .placement = PropertyReader::Get<Api::WindowPlacementProps>(propertyMap, Api::Props::Placement),
        .resizable = PropertyReader::Get<bool>(propertyMap, Api::Props::Resizable),
        .topMost = PropertyReader::Get<bool>(propertyMap, Api::Props::TopMost),
        .taskbar = PropertyReader::Get<bool>(propertyMap, Api::Props::Taskbar),
        .visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible),
        .minSize = PropertyReader::Get<Api::Size>(propertyMap, Api::Props::MinSize),
        .maxSize = PropertyReader::Get<Api::Size>(propertyMap, Api::Props::MaxSize),
        .state = PropertyReader::Get<Api::WindowState>(propertyMap, Api::Props::State),
    };
}

auto RemoveWindowProps(Api::PropertyMap& propertyMap) -> void
{
    propertyMap.erase(Api::Props::Rect);
    propertyMap.erase(Api::Props::Size);
    propertyMap.erase(Api::Props::Icon);
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

auto IsNormal(const Props& props) -> bool
{
    return !props.state || *props.state == Api::WindowState::Normal;
}

auto ApplySettings(NativeWindow& window, const Props& props) -> void
{
    const auto hwnd = window.handle();

    if (props.icon && !props.icon->empty()) NativeWindowApi::SetIcon(hwnd, *props.icon);
    if (props.caption) NativeWindowStyle::SetCaption(hwnd, *props.caption);
    if (props.resizable) NativeWindowStyle::SetResizable(hwnd, *props.resizable);
    if (props.taskbar) NativeWindowStyle::SetTaskbar(hwnd, *props.taskbar);
    if (props.topMost) NativeWindowApi::SetTopMost(hwnd, *props.topMost);
    if (props.minSize) window.setMinSize(*props.minSize);
    if (props.maxSize) window.setMaxSize(*props.maxSize);
}

auto ApplyBounds(HWND hwnd, const Props& props) -> void
{
    if (props.rect)
    {
        LOGF_D(L" -> Apply::%s %s", to_string(Api::Props::Rect).c_str(), to_string(*props.rect).c_str());
        if (IsNormal(props))
        {
            NativeApi::SetClientRect(hwnd, *props.rect);
        }
        else
        {
            NativeWindowApi::SetNormalRect(hwnd, {props.rect->position(), NativeApi::ClientToWindowSize(hwnd, props.rect->size())});
        }
    }
    else if (props.size)
    {
        LOGF_D(L" -> Apply::%s %s", to_string(Api::Props::Size).c_str(), to_string(*props.size).c_str());
        if (IsNormal(props)) NativeApi::SetClientSize(hwnd, *props.size);
    }
}

auto ApplyPlacement(HWND hwnd, const Props& props, Api::PropertyMap& nativeProps) -> void
{
    if (!props.placement) return;

    if (IsNormal(props) || !props.size)
    {
        NativeWindowApi::SetPlacement(hwnd, *props.placement);
    }
    else
    {
        NativeWindowApi::SetNormalPlacement(hwnd, *props.placement, NativeApi::ClientToWindowSize(hwnd, *props.size));
    }

    nativeProps.erase(Api::Props::Position);
}

auto ApplyVisibility(HWND hwnd, const Props& props) -> void
{
    if (props.visible && !*props.visible)
    {
        NativeApi::SetVisible(hwnd, false);
    }
    else if (props.state)
    {
        NativeWindowApi::SetState(hwnd, *props.state);
    }
    else if (props.visible)
    {
        NativeApi::SetVisible(hwnd, true);
    }
}

} // namespace

auto NativeWindowProps::Apply(NativeWindow& window, const Api::PropertyMap& propertyMap) -> Api::PropertyMap
{
    Api::PropertyMap nativeProps = propertyMap;
    RemoveWindowProps(nativeProps);

    const auto hwnd = window.handle();
    const auto props = GetProps(propertyMap);

    ApplySettings(window, props);
    ApplyBounds(hwnd, props);
    ApplyPlacement(hwnd, props, nativeProps);
    ApplyVisibility(hwnd, props);

    return nativeProps;
}

} // namespace Blade::Backend

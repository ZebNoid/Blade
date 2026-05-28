#include "NativeWindowProps.h"

#include "Components/Window/NativeWindow.h"
#include "Common/Logger.h"
#include "NativeWindowApi/NativeWindowApi.h"
#include "NativeWindowPropsData/NativeWindowPropsData.h"
#include "NativeWindowStyle/NativeWindowStyle.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

namespace {

auto ApplySettings(NativeWindow& window, const NativeWindowPropsData& props) -> void
{
    const auto hwnd = window.handle();

    if (props.icon && !props.icon->empty()) NativeWindowApi::SetIcon(hwnd, *props.icon);
    if (props.caption) NativeWindowStyle::SetCaption(hwnd, *props.caption);
    if (props.resizable) NativeWindowStyle::SetResizable(hwnd, *props.resizable);
    if (props.taskbar) NativeWindowStyle::SetTaskbar(hwnd, *props.taskbar);
    if (props.topMost) NativeWindowApi::SetTopMost(hwnd, *props.topMost);
    if (props.minSize) window.setMinSize(*props.minSize);
    if (props.maxSize) window.setMaxSize(*props.maxSize);
    if (props.contextMenus) window.enableContextMenus(*props.contextMenus);
    if (props.lifetime) window.setLifetime(*props.lifetime);
}

auto ApplyBounds(HWND hwnd, const NativeWindowPropsData& props) -> void
{
    if (props.rect)
    {
        if (props.isNormal())
        {
            HwndApi::SetClientRect(hwnd, *props.rect);
        }
        else
        {
            NativeWindowApi::SetNormalRect(hwnd, {props.rect->position(), HwndApi::ClientToWindowSize(hwnd, props.rect->size())});
        }
    }
    else if (props.size)
    {
        if (props.isNormal()) HwndApi::SetClientSize(hwnd, *props.size);
    }
}

auto ApplyPlacement(HWND hwnd, const NativeWindowPropsData& props, Api::PropertyMap& nativeProps) -> void
{
    if (!props.placement) return;

    if (props.isNormal() || !props.size)
    {
        NativeWindowApi::SetPlacement(hwnd, *props.placement);
    }
    else
    {
        NativeWindowApi::SetNormalPlacement(hwnd, *props.placement, HwndApi::ClientToWindowSize(hwnd, *props.size));
    }

    nativeProps.erase(Api::Props::Position);
}

auto ApplyVisibility(HWND hwnd, const NativeWindowPropsData& props) -> void
{
    if (props.visible && !*props.visible)
    {
        HwndApi::SetVisible(hwnd, false);
    }
    else if (props.state)
    {
        NativeWindowApi::SetState(hwnd, *props.state);
    }
    else if (props.visible)
    {
        HwndApi::SetVisible(hwnd, true);
    }
}

} // namespace

auto NativeWindowProps::Apply(NativeWindow& window, const Api::PropertyMap& propertyMap) -> Api::PropertyMap
{
    Api::PropertyMap nativeProps = propertyMap;
    NativeWindowPropsData::RemoveHandled(nativeProps);

    const auto hwnd = window.handle();
    const auto props = NativeWindowPropsData::Read(propertyMap);

    ApplySettings(window, props);
    ApplyBounds(hwnd, props);
    ApplyPlacement(hwnd, props, nativeProps);
    ApplyVisibility(hwnd, props);

    return nativeProps;
}

} // namespace Blade::Backend

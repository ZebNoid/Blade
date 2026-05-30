#include "NativeWindowPlacement.h"

#include "WinApi/Display/DisplayApi/DisplayApi.h"
#include "WinApi/HwndApi/HwndApi.h"

namespace Blade::Backend {

namespace {

auto FillSize(const Api::WindowPlacementProps& placement, Api::Rect screen, Api::Size size) -> Api::Size
{
    switch (placement.anchor)
    {
    case Api::WindowAnchor::TopFill:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::BottomFill:
    case Api::WindowAnchor::Fill:
        size.width = screen.width;
        break;

    default:
        break;
    }

    switch (placement.anchor)
    {
    case Api::WindowAnchor::LeftFill:
    case Api::WindowAnchor::CenterVerticalFill:
    case Api::WindowAnchor::RightFill:
    case Api::WindowAnchor::Fill:
        size.height = screen.height;
        break;

    default:
        break;
    }

    return size;
}

auto X(const Api::WindowPlacementProps& placement, Api::Rect screen, Api::Size size) -> int
{
    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        return placement.offset.x;

    case Api::WindowAnchor::TopCenter:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::CenterHorizontalFill:
    case Api::WindowAnchor::CenterVerticalFill:
        return screen.x + (screen.width - size.width) / 2 + placement.offset.x;

    case Api::WindowAnchor::TopRight:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::RightFill:
        return screen.x + screen.width - size.width + placement.offset.x;

    default:
        return screen.x + placement.offset.x;
    }
}

auto Y(const Api::WindowPlacementProps& placement, Api::Rect screen, Api::Size size) -> int
{
    switch (placement.anchor)
    {
    case Api::WindowAnchor::Manual:
        return placement.offset.y;

    case Api::WindowAnchor::CenterLeft:
    case Api::WindowAnchor::Center:
    case Api::WindowAnchor::CenterRight:
    case Api::WindowAnchor::CenterHorizontalFill:
        return screen.y + (screen.height - size.height) / 2 + placement.offset.y;

    case Api::WindowAnchor::BottomLeft:
    case Api::WindowAnchor::BottomCenter:
    case Api::WindowAnchor::BottomRight:
    case Api::WindowAnchor::BottomFill:
        return screen.y + screen.height - size.height + placement.offset.y;

    default:
        return screen.y + placement.offset.y;
    }
}

} // namespace

auto NativeWindowPlacement::ToRect(HWND hwnd, const Api::WindowPlacementProps& placement) -> Api::Rect
{
    return ToRect(placement, HwndApi::GetSize(hwnd));
}

auto NativeWindowPlacement::ToRect(const Api::WindowPlacementProps& placement, Api::Size size) -> Api::Rect
{
    const auto screen = DisplayApi::WorkArea(placement.monitor);
    size = FillSize(placement, screen, size);

    return {
        X(placement, screen, size),
        Y(placement, screen, size),
        size.width,
        size.height
    };
}

auto NativeWindowPlacement::ToWinRect(const Api::Rect& rect) -> RECT
{
    return {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
}

} // namespace Blade::Backend

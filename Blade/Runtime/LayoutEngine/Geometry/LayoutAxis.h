#pragma once

#include "Geometry/Rect.h"
#include "Geometry/Size.h"


namespace Blade {

enum class LayoutAxis
{
    Horizontal,
    Vertical
};

namespace Layout::Axis {

    inline auto MainSize(LayoutAxis axis, const Api::Size& size) -> int
    {
        return axis == LayoutAxis::Horizontal ? size.width : size.height;
    }

    inline auto CrossSize(LayoutAxis axis, const Api::Size& size) -> int
    {
        return axis == LayoutAxis::Horizontal ? size.height : size.width;
    }

    inline auto MainRectSize(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.width : rect.height;
    }

    inline auto CrossRectSize(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.height : rect.width;
    }

    inline auto MainRectPosition(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.x : rect.y;
    }

    inline auto CrossRectPosition(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.y : rect.x;
    }

    inline auto Size(LayoutAxis axis, int mainSize, int crossSize) -> Api::Size
    {
        return axis == LayoutAxis::Horizontal
            ? Api::Size{mainSize, crossSize}
            : Api::Size{crossSize, mainSize};
    }

    inline auto Rect(LayoutAxis axis, int mainPosition, int crossPosition, int mainSize, int crossSize) -> Api::Rect
    {
        return axis == LayoutAxis::Horizontal
            ? Api::Rect{mainPosition, crossPosition, mainSize, crossSize}
            : Api::Rect{crossPosition, mainPosition, crossSize, mainSize};
    }

} // namespace Layout::Axis

} // namespace Blade

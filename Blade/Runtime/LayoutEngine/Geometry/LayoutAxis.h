#pragma once

#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Thickness.h"


namespace Blade {

enum class LayoutAxis
{
    Horizontal,
    Vertical
};

class LayoutAxisGeometry
{
public:
    static auto MainSize(LayoutAxis axis, const Api::Size& size) -> int
    {
        return axis == LayoutAxis::Horizontal ? size.width : size.height;
    }

    static auto CrossSize(LayoutAxis axis, const Api::Size& size) -> int
    {
        return axis == LayoutAxis::Horizontal ? size.height : size.width;
    }

    static auto MainRectSize(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.width : rect.height;
    }

    static auto CrossRectSize(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.height : rect.width;
    }

    static auto MainRectPosition(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.x : rect.y;
    }

    static auto CrossRectPosition(LayoutAxis axis, const Api::Rect& rect) -> int
    {
        return axis == LayoutAxis::Horizontal ? rect.y : rect.x;
    }

    static auto MainMarginStart(LayoutAxis axis, const Api::Thickness& margin) -> int
    {
        return axis == LayoutAxis::Horizontal ? margin.left : margin.top;
    }

    static auto MainMarginEnd(LayoutAxis axis, const Api::Thickness& margin) -> int
    {
        return axis == LayoutAxis::Horizontal ? margin.right : margin.bottom;
    }

    static auto CrossMarginStart(LayoutAxis axis, const Api::Thickness& margin) -> int
    {
        return axis == LayoutAxis::Horizontal ? margin.top : margin.left;
    }

    static auto CrossMarginEnd(LayoutAxis axis, const Api::Thickness& margin) -> int
    {
        return axis == LayoutAxis::Horizontal ? margin.bottom : margin.right;
    }

    static auto Size(LayoutAxis axis, int mainSize, int crossSize) -> Api::Size
    {
        return axis == LayoutAxis::Horizontal
            ? Api::Size{mainSize, crossSize}
            : Api::Size{crossSize, mainSize};
    }

    static auto Rect(LayoutAxis axis, int mainPosition, int crossPosition, int mainSize, int crossSize) -> Api::Rect
    {
        return axis == LayoutAxis::Horizontal
            ? Api::Rect{mainPosition, crossPosition, mainSize, crossSize}
            : Api::Rect{crossPosition, mainPosition, crossSize, mainSize};
    }
};

} // namespace Blade

#pragma once

#include "Geometry/Rect.h"
#include "Geometry/Size.h"
#include "Geometry/Thickness.h"
#include "Props/LayoutProps/MainAxisAlignment.h"


namespace Blade {

namespace Layout::Geometry {

    inline auto NonNegative(int value) -> int
    {
        return max(0, value);
    }

    inline auto Inflate(const Api::Size& size, const Api::Thickness& thickness) -> Api::Size
    {
        return {
            size.width + thickness.left + thickness.right,
            size.height + thickness.top + thickness.bottom
        };
    }

    inline auto Deflate(const Api::Rect& rect, const Api::Thickness& thickness) -> Api::Rect
    {
        return {
            rect.x + thickness.left,
            rect.y + thickness.top,
            NonNegative(rect.width - thickness.left - thickness.right),
            NonNegative(rect.height - thickness.top - thickness.bottom)
        };
    }

    inline auto Constrain(const Api::Size& size, const Api::Size& minSize, const Api::Size& maxSize) -> Api::Size
    {
        auto result = size;

        if (minSize.width > 0) result.width = max(result.width, minSize.width);
        if (minSize.height > 0) result.height = max(result.height, minSize.height);
        if (maxSize.width > 0) result.width = min(result.width, maxSize.width);
        if (maxSize.height > 0) result.height = min(result.height, maxSize.height);

        return result;
    }

    inline auto MainAxisOffset(MainAxisAlignment alignment, int available, int content, int itemCount) -> int
    {
        const int freeSpace = NonNegative(available - content);

        switch (alignment)
        {
        case MainAxisAlignment::Center:
            return freeSpace / 2;

        case MainAxisAlignment::End:
            return freeSpace;

        case MainAxisAlignment::SpaceAround:
            return itemCount > 0
                ? freeSpace / (itemCount * 2)
                : 0;

        case MainAxisAlignment::SpaceEvenly:
            return itemCount > 0
                ? freeSpace / (itemCount + 1)
                : 0;

        case MainAxisAlignment::Start:
        case MainAxisAlignment::SpaceBetween:
        default:
            return 0;
        }
    }

    inline auto MainAxisGap(MainAxisAlignment alignment, int baseGap, int available, int content, int itemCount) -> int
    {
        const int freeSpace = NonNegative(available - content);

        switch (alignment)
        {
        case MainAxisAlignment::SpaceBetween:
            return itemCount > 1
                ? baseGap + freeSpace / (itemCount - 1)
                : baseGap;

        case MainAxisAlignment::SpaceAround:
            return itemCount > 0
                ? baseGap + freeSpace / itemCount
                : baseGap;

        case MainAxisAlignment::SpaceEvenly:
            return itemCount > 0
                ? baseGap + freeSpace / (itemCount + 1)
                : baseGap;

        case MainAxisAlignment::Start:
        case MainAxisAlignment::Center:
        case MainAxisAlignment::End:
        default:
            return baseGap;
        }
    }

} // namespace Layout::Geometry

} // namespace Blade

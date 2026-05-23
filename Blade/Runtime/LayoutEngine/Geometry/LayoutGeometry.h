#pragma once

#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Thickness.h"
#include "Props/LayoutProps/MainAxisAlignment.h"


namespace Blade {

class LayoutGeometry
{
public:
    static auto NonNegative(
        int value
    ) -> int
    {
        return max(
            0,
            value
        );
    }

    static auto Inflate(
        const Api::Size& size,
        const Api::Thickness& thickness
    ) -> Api::Size
    {
        return {
            size.width +
            thickness.left +
            thickness.right,

            size.height +
            thickness.top +
            thickness.bottom
        };
    }

    static auto Deflate(
        const Api::Rect& rect,
        const Api::Thickness& thickness
    ) -> Api::Rect
    {
        return {
            rect.x + thickness.left,
            rect.y + thickness.top,

            NonNegative(
                rect.width -
                thickness.left -
                thickness.right
            ),

            NonNegative(
                rect.height -
                thickness.top -
                thickness.bottom
            )
        };
    }

    static auto MainAxisOffset(
        const MainAxisAlignment alignment,
        const int available,
        const int content,
        const int itemCount
    ) -> int
    {
        const int freeSpace =
            NonNegative(
                available -
                content
            );

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

    static auto MainAxisGap(
        const MainAxisAlignment alignment,
        const int baseGap,
        const int available,
        const int content,
        const int itemCount
    ) -> int
    {
        const int freeSpace =
            NonNegative(
                available -
                content
            );

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
};

} // namespace Blade

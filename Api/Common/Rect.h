#pragma once
#include "Point.h"
#include "Size.h"

namespace Blade::Api {

struct Rect
{
    int x{};
    int y{};
    int width{};
    int height{};

    Rect() = default;

    Rect(
        int x,
        int y,
        int width,
        int height
    )
        : x(x),
          y(y),
          width(width),
          height(height)
    {
    }

    Rect(
        const Point& position,
        const Size& size
    )
        : x(position.x),
          y(position.y),
          width(size.width),
          height(size.height)
    {
    }

    auto position() const -> Point
    {
        return {
            x,
            y
        };
    }

    auto size() const -> Size
    {
        return {
            width,
            height
        };
    }
};

} // namespace

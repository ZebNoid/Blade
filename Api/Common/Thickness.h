#pragma once

namespace Blade::Api {


struct Thickness
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;

    Thickness() = default;

    Thickness(const int all)
        : left(all),
          top(all),
          right(all),
          bottom(all)
    {
    }

    Thickness(
        const int horizontal,
        const int vertical
    )
        : left(horizontal),
          top(vertical),
          right(horizontal),
          bottom(vertical)
    {
    }

    Thickness(
        const int left,
        const int top,
        const int right,
        const int bottom
    )
        : left(left),
          top(top),
          right(right),
          bottom(bottom)
    {
    }
};


} // namespace

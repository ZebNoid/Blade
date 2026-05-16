#pragma once

struct Thickness
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;

    Thickness() = default;

    Thickness(int all)
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
        int left,
        int top,
        int right,
        int bottom
    )
        : left(left),
          top(top),
          right(right),
          bottom(bottom)
    {
    }
};

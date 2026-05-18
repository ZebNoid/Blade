#pragma once

#include <windows.h>


namespace Blade {

namespace Debug{
    static bool debug = false;
}

struct LayoutDebugTheme
{
    static constexpr COLORREF Bounds = RGB(0, 165, 0);

    static constexpr COLORREF Margin = RGB(0, 255, 165);

    static constexpr COLORREF Padding = RGB(0, 165, 255);

    static constexpr COLORREF Text = RGB(0, 165, 0);

    static constexpr int WidthBounds = 1;
    static constexpr int WidthMargin = 1;
    static constexpr int WidthPadding = 1;

    static constexpr int Inflate = 0;
};

} // namespace

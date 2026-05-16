#pragma once

#include <windows.h>


namespace Blade {


struct LayoutDebugTheme
{
    static constexpr COLORREF WidgetBounds = RGB(255, 0, 0);

    static constexpr COLORREF Margin = RGB(255, 165, 0);

    static constexpr COLORREF Padding = RGB(0, 165, 0);

    static constexpr COLORREF Text = RGB(255, 165, 165);

    static constexpr int Width = 2;

    static constexpr int Inflate = 1;
};

} // namespace

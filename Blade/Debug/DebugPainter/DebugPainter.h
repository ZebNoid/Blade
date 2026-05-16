#pragma once

#include <string>
#include <windows.h>

#include "Props/Common/LayoutProps.h"


namespace Blade {


class DebugPainter
{
public:
    static auto DrawBounds(HDC hdc, Rect rect) -> void;

    static auto DrawMargin(HDC hdc, Rect rect, LayoutProps layout) -> void;

    static auto DrawPadding(HDC hdc, Rect rect, LayoutProps layout) -> void;

    static auto DrawText(HDC hdc, Rect rect, const std::wstring& text) -> void;
};


} // namespace

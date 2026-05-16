#pragma once

#include <windows.h>


namespace Blade {


class NativeDraw
{
public:
    static auto DrawDebugText(
        HDC hdc,
        const Rect& rect,
        COLORREF color,
        const std::wstring& text
    ) -> void;

    static auto DrawFilledRect(
        HDC hdc,
        const RECT& rect,
        HBRUSH brush
    ) -> void;

    static auto DrawOutlineRect(
        HDC hdc,
        const RECT& rect,
        HPEN pen,
        // COLORREF color,
        // int width = 1,
        int inflate = 0
    ) -> void;
};


} // namespace

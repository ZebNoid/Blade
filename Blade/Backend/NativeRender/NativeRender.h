#pragma once

#include <string>
#include <windows.h>


namespace Blade::Backend {


class NativeRender
{
public:
    auto rectFill(
        HDC hdc,
        RECT rect,
        COLORREF color
    ) -> void;

    auto rectBorder(
        HDC hdc,
        RECT rect,
        COLORREF color,
        int thickness = 1
    ) -> void;

    auto line(
        HDC hdc,
        int x1, int y1,
        int x2, int y2,
        COLORREF color,
        int thickness = 1
    ) -> void;

    auto text(
        HDC hdc,
        RECT rect,
        const std::wstring& text,
        COLORREF color
    ) -> void;
};

} // namespace

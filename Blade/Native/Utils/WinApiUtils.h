#pragma once

#include <windows.h>
#include <cstdio>

// EDIT text verticel align
inline auto VerticalAlignCenter(const HWND hwnd) -> void
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    // Calculate text height (this is a simplified example)
    TEXTMETRIC tm;
    const HDC hdc = GetDC(hwnd);
    // SelectObject(hdc, GetWindowFont(hwnd)); // MFC
    SelectObject(hdc, (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0));
    GetTextMetrics(hdc, &tm);
    ReleaseDC(hwnd, hdc);

    // text vertical align center
    auto lineHeight = tm.tmHeight + tm.tmExternalLeading;
    auto lineCount = (int)SendMessage(hwnd, EM_GETLINECOUNT, 0, 0);
    auto textHeight = lineHeight * lineCount;

    if (rc.bottom > textHeight)
    {
        // Adjust rectangle
        rc.top = (rc.bottom - textHeight) / 2 - tm.tmInternalLeading;
    }

    // int lineLen = (int)SendMessage(hwnd, EM_LINELENGTH, lineIndex, 0);
    // auto tl = GetWindowTextLength(hwnd);
    // std::printf("%d %ld %d\n", lineHeight, tm.tmHeight,  lineCount);
    // std::printf("%ld %ld\n", rc.bottom, textHeight); // TODO log


    // Final Text paddings
    rc.top += tm.tmInternalLeading;
    rc.bottom -= tm.tmInternalLeading;
    rc.left += tm.tmInternalLeading;
    rc.right -= tm.tmInternalLeading;

    SendMessage(hwnd, EM_SETRECT, 0, (LPARAM)&rc);
}

inline auto center(const Size size) -> Point
{
    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Calculate centered position
    const int xPos = (screenWidth - size.width) / 2;
    const int yPos = (screenHeight - size.height) / 2;
    return {xPos, yPos};
}

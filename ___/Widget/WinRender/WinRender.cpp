#include "WinRender.h"


namespace Blade::Backend {


auto WinRender::rect(
    HDC hdc,
    RECT rect,
    COLORREF color,
    int thickness
) -> void
{
    HPEN pen = CreatePen(
        PS_SOLID,
        thickness,
        color
    );

    // TODO ResourceManager!!
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

    Rectangle(
        hdc,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom
    );

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);

    // TODO ResourceManager!!
    DeleteObject(pen);
}

auto WinRender::rectFill(
    HDC hdc,
    RECT rect,
    COLORREF color
) -> void
{
    // TODO ResourceManager!!
    HBRUSH brush = CreateSolidBrush(color);
    ::FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}


auto WinRender::frame(
    HDC hdc,
    RECT rect,
    COLORREF color
) -> void
{
    // TODO ResourceManager!!
    HBRUSH brush = CreateSolidBrush(color);
    ::FrameRect(hdc, &rect, brush);
    DeleteObject(brush);
}


auto WinRender::line(
    HDC hdc,
    int x1, int y1,
    int x2, int y2,
    COLORREF color,
    int thickness
) -> void
{
    // TODO ResourceManager!!
    HPEN pen = CreatePen(
        PS_SOLID,
        thickness,
        color
    );

    HGDIOBJ oldPen = SelectObject(hdc, pen);

    ::MoveToEx(hdc, x1, y1, nullptr);
    ::LineTo(hdc, x2, y2);

    SelectObject(hdc, oldPen);

    // TODO ResourceManager!!
    DeleteObject(pen);
}

auto WinRender::text(
    HDC hdc,
    RECT rect,
    const std::wstring& text,
    COLORREF color,
    HFONT font,
    int style
) -> void
{
    // выбрать font
    HFONT oldFont = nullptr;

    if (font)
    {
        oldFont = (HFONT)SelectObject(hdc, font);
    }

    // SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, color);

    ::DrawTextW(
        hdc,
        text.c_str(),
        -1,
        &rect,
        // DT_CENTER |
        DT_VCENTER |
        DT_SINGLELINE |
        DT_END_ELLIPSIS | style
    );

    if (oldFont)
    {
        SelectObject(hdc, oldFont);
    }
}

} // namespace

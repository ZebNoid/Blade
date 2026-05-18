#include "NativeRender.h"


namespace Blade::Backend {


auto NativeRender::rect(
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

auto NativeRender::rectFill(
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


auto NativeRender::frame(
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


auto NativeRender::line(
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

auto NativeRender::text(
    HDC hdc,
    RECT rect,
    const std::wstring& text,
    COLORREF color
) -> void
{
    // SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, color);

    ::DrawTextW(
        hdc,
        text.c_str(),
        -1,
        &rect,
        DT_CENTER |
        DT_VCENTER |
        DT_SINGLELINE
    );
}

} // namespace

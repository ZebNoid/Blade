#include "NativeDraw.h"


namespace Blade::Backend {


auto NativeDraw::DrawDebugText(
    HDC hdc,
    const Rect& rect,
    COLORREF color,
    const std::wstring& text

) -> void
{
    SetBkMode(
        hdc,
        TRANSPARENT
    );

    SetTextColor(
        hdc,
        color
    );

    SIZE textSize = {0};

    // 2. Calculate the bounds
    GetTextExtentPoint32W(hdc, text.c_str(), text.size(), &textSize);

    TextOutW(
        hdc,
        // TODO Debug text center
        rect.x + (rect.width - textSize.cx) / 2,
        rect.y + (rect.height - textSize.cy) / 2,
        // rect.x + 8,
        // rect.y + 8,
        text.c_str(),
        static_cast<int>(text.size())
    );
}

auto NativeDraw::DrawFilledRect(
    HDC hdc,
    const RECT& rect,
    HBRUSH brush
    // COLORREF color
    // HBRUSH brush = CreateSolidBrush(color);
) -> void
{
    FillRect(
        hdc,
        &rect,
        brush
    );

    // DeleteObject(brush);
}

auto NativeDraw::DrawOutlineRect(
    HDC hdc,
    const RECT& rect,
    HPEN pen,
    // COLORREF color,
    // int width,
    int inflate
) -> void
{
    // HPEN pen = CreatePen(PS_SOLID, width, color);

    auto oldPen =
        static_cast<HPEN>(
            SelectObject(hdc, pen)
        );

    auto oldBrush =
        static_cast<HBRUSH>(
            SelectObject(hdc, GetStockObject(NULL_BRUSH))
        );

    if (inflate > 0)
    {
        InflateRect((LPRECT)&rect, inflate, inflate);
    }

    // Debug bound rect
    Rectangle(
        hdc,
        rect.left - 1,
        rect.top - 1,
        rect.right + 1,
        rect.bottom + 1
    );

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);

    // DeleteObject(g_boundsPen); // TODO
}

} // namespace

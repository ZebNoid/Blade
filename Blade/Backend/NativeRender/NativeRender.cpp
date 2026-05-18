#include "NativeRender.h"


namespace Blade::Backend {

auto NativeRender::FillRect(
    NativeRenderContext& ctx,
    Rect rect,
    Color color
) -> void
{
    // TODO ResourceManager!!
    HBRUSH brush = CreateSolidBrush(
        RGB(color.r, color.g, color.b)
    );

    RECT rc{
        rect.x,
        rect.y,
        rect.x + rect.width,
        rect.y + rect.height
    };

    ::FillRect(ctx.hdc, &rc, brush);

    // TODO ResourceManager!!
    DeleteObject(brush);
}


auto NativeRender::DrawRect(
    NativeRenderContext& ctx,
    Rect rect,
    Color color,
    int thickness
) -> void
{
    HPEN pen = CreatePen(
        PS_SOLID,
        thickness,
        RGB(color.r, color.g, color.b)
    );

    // TODO ResourceManager!!
    HGDIOBJ oldPen = SelectObject(ctx.hdc, pen);

    HGDIOBJ oldBrush = SelectObject(ctx.hdc, GetStockObject(HOLLOW_BRUSH));

    Rectangle(
        ctx.hdc,
        rect.x,
        rect.y,
        rect.x + rect.width,
        rect.y + rect.height
    );

    SelectObject(ctx.hdc, oldPen);
    SelectObject(ctx.hdc, oldBrush);

    // TODO ResourceManager!!
    DeleteObject(pen);
}


auto NativeRender::DrawLine(
    NativeRenderContext& ctx,
    int x1, int y1,
    int x2, int y2,
    Color color,
    int thickness
) -> void
{
    // TODO ResourceManager!!
    HPEN pen = CreatePen(
        PS_SOLID,
        thickness,
        RGB(color.r, color.g, color.b)
    );

    HGDIOBJ oldPen = SelectObject(ctx.hdc, pen);

    MoveToEx(ctx.hdc, x1, y1, nullptr);

    LineTo(ctx.hdc, x2, y2);

    SelectObject(ctx.hdc, oldPen);

    // TODO ResourceManager!!
    DeleteObject(pen);
}

auto NativeRender::DrawText(
    NativeRenderContext& ctx,
    Rect rect,
    const std::wstring& text,
    Color color
) -> void
{
    SetBkMode(ctx.hdc, TRANSPARENT);

    SetTextColor(
        ctx.hdc,
        RGB(color.r, color.g, color.b)
    );

    RECT rc{
        rect.x,
        rect.y,
        rect.x + rect.width,
        rect.y + rect.height
    };

    ::DrawTextW(
        ctx.hdc,
        text.c_str(),
        -1,
        &rc,
        DT_CENTER |
        DT_VCENTER |
        DT_SINGLELINE
    );
}

} // namespace

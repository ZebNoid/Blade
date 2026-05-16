#include "LayoutDebugRenderer.h"

#include "Widgets/Widget/Widget.h"
#include "Props/Common/Thickness.h"


namespace Blade {


namespace {
    auto DrawFilledRect(
        HDC hdc,
        const RECT& rect,
        COLORREF color
    ) -> void
    {
        HBRUSH brush = CreateSolidBrush(color);

        FillRect(
            hdc,
            &rect,
            brush
        );

        DeleteObject(brush);
    }

    auto DrawOutlineRect(
        HDC hdc,
        const RECT& rect,
        COLORREF color
    ) -> void
    {
        HPEN pen = CreatePen(PS_SOLID, 1, color);

        auto oldPen =
            static_cast<HPEN>(
                SelectObject(hdc, pen)
            );

        auto oldBrush =
            static_cast<HBRUSH>(
                SelectObject(hdc, GetStockObject(NULL_BRUSH))
            );

        Rectangle(
            hdc,
            rect.left,
            rect.top,
            rect.right,
            rect.bottom
        );

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);

        DeleteObject(pen);
    }
}


auto LayoutDebugRenderer::Render(
    HDC hdc,
    Widget& widget
) -> void
{
    const auto rect = widget.rect();

    RECT widgetRect = {
        rect.x,
        rect.y,
        rect.x + rect.width,
        rect.y + rect.height
    };

    // -------------------------------------------------
    // Widget bounds
    // -------------------------------------------------

    DrawOutlineRect(
        hdc,
        widgetRect,
        RGB(255, 0, 0)
    );

    // -------------------------------------------------
    // Padding
    // -------------------------------------------------

    const auto& padding =
        widget.layout().padding;

    RECT paddingRect = {
        rect.x + padding.left,
        rect.y + padding.top,

        rect.x + rect.width - padding.right,
        rect.y + rect.height - padding.bottom
    };

    DrawOutlineRect(
        hdc,
        paddingRect,
        RGB(0, 255, 0)
    );

    // -------------------------------------------------
    // Margin
    // -------------------------------------------------

    const auto& margin =
        widget.layout().margin;

    RECT marginRect = {
        rect.x - margin.left,
        rect.y - margin.top,

        rect.x + rect.width + margin.right,
        rect.y + rect.height + margin.bottom
    };

    DrawOutlineRect(
        hdc,
        marginRect,
        RGB(255, 165, 0)
    );

    // -------------------------------------------------
    // Children
    // -------------------------------------------------

    for (const auto& child : widget.children())
    {
        Render(
            hdc,
            *child
        );
    }
}

} // namespace

#include "LayoutDebugRenderer.h"

#include "LayoutDebugTheme.h"
#include "Widgets/Widget/Widget.h"
#include "Props/Common/Thickness.h"


namespace Blade {


namespace {

    auto DrawDebugText(
        HDC hdc,
        const Rect& rect,
        const std::wstring& text
    ) -> void
    {
        SetBkMode(
            hdc,
            TRANSPARENT
        );

        SetTextColor(
            hdc,
            LayoutDebugTheme::Text
        );

        SIZE textSize = { 0 };

        // 2. Calculate the bounds
        GetTextExtentPoint32W(hdc, text.c_str(), text.size(), &textSize);

        TextOutW(
            hdc,
            rect.x + (rect.width - textSize.cx)/2,
            rect.y + (rect.height - textSize.cy)/2,
            text.c_str(),
            static_cast<int>(text.size())
        );
    }

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
        COLORREF color,
        int width = 1,
        int inflate = 0
    ) -> void
    {
        HPEN pen = CreatePen(PS_SOLID, width, color);

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

    DrawDebugText(hdc, rect, widget.name());

    // -------------------------------------------------
    // Widget bounds
    // -------------------------------------------------

    DrawOutlineRect(
        hdc,
        widgetRect,
        LayoutDebugTheme::WidgetBounds,
        LayoutDebugTheme::Width,
        LayoutDebugTheme::Inflate
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
        LayoutDebugTheme::Padding,
        LayoutDebugTheme::Width,
        LayoutDebugTheme::Inflate
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
        LayoutDebugTheme::Margin,
        LayoutDebugTheme::Width,
        LayoutDebugTheme::Inflate
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

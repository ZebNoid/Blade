#include "DebugPainter.h"

#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"
#include "Debug/LayoutDebugRenderer/LayoutDebugTheme.h"
#include "Debug/NativeDraw/NativeDraw.h"


namespace Blade {


auto DebugPainter::DrawBounds(HDC hdc, Rect rect) -> void
{
    // -------------------------------------------------
    // Widget bounds
    // -------------------------------------------------

    RECT widgetRect = {
        rect.x,
        rect.y,
        rect.x + rect.width,
        rect.y + rect.height
    };

    NativeDraw::DrawOutlineRect(
        hdc,
        widgetRect,
        ResourceRegistry::GetPen("debug_bounds", LayoutDebugTheme::Bounds, LayoutDebugTheme::WidthBounds),
        LayoutDebugTheme::Inflate
    );
}

auto DebugPainter::DrawMargin(HDC hdc, Rect rect, LayoutProps layout) -> void
{
    // -------------------------------------------------
    // Margin
    // -------------------------------------------------

    RECT marginRect = {
        rect.x - layout.margin.left,
        rect.y - layout.margin.top,

        rect.x + rect.width + layout.margin.right,
        rect.y + rect.height + layout.margin.bottom
    };

    NativeDraw::DrawOutlineRect(
        hdc,
        marginRect,
        ResourceRegistry::GetPen("debug_margin", LayoutDebugTheme::Margin, LayoutDebugTheme::WidthMargin),
        LayoutDebugTheme::Inflate
    );
}


auto DebugPainter::DrawPadding(HDC hdc, Rect rect, LayoutProps layout) -> void
{
    // -------------------------------------------------
    // Padding
    // -------------------------------------------------

    RECT paddingRect = {
        rect.x + layout.padding.left,
        rect.y + layout.padding.top,

        rect.x + rect.width - layout.padding.right,
        rect.y + rect.height - layout.padding.bottom
    };

    NativeDraw::DrawOutlineRect(
        hdc,
        paddingRect,
        ResourceRegistry::GetPen("debug_padding", LayoutDebugTheme::Padding, LayoutDebugTheme::WidthMargin),
        LayoutDebugTheme::Inflate
    );
}

auto DebugPainter::DrawTextW(HDC hdc, Rect rect, const std::wstring& text) -> void
{
    NativeDraw::DrawDebugText(
        hdc,
        rect,
        LayoutDebugTheme::Text,
        text
    );
}

} // namespace

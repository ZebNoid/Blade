#include "DebugPainter.h"

#include "Debug/LayoutDebugRenderer/LayoutDebugTheme.h"
#include "Debug/NativeDraw/NativeDraw.h"


namespace Blade {

namespace {
    // TODO move to rsource manager
    HPEN g_boundsPen = nullptr;
    HPEN g_marginPen = nullptr;
    HPEN g_paddingPen = nullptr;
}


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


    if (!g_boundsPen)
    {
        g_boundsPen = CreatePen(PS_SOLID, LayoutDebugTheme::Width, LayoutDebugTheme::WidgetBounds);
    }

    NativeDraw::DrawOutlineRect(
        hdc,
        widgetRect,
        g_boundsPen,
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

    if (!g_marginPen)
    {
        g_marginPen = CreatePen(PS_SOLID, LayoutDebugTheme::Width, LayoutDebugTheme::Margin);
    }

    NativeDraw::DrawOutlineRect(
        hdc,
        marginRect,
        g_marginPen,
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

    if (!g_paddingPen)
    {
        g_paddingPen = CreatePen(PS_SOLID, LayoutDebugTheme::Width, LayoutDebugTheme::Padding);
    }

    NativeDraw::DrawOutlineRect(
        hdc,
        paddingRect,
        g_paddingPen,
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

#include "LayoutDebugRenderer.h"

#include "Debug/LayoutDebugTheme.h"
#include "Debug/DebugPainter/DebugPainter.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


auto LayoutDebugRenderer::Render(HDC hdc, Widget& widget) -> void
{
    if (Debug::debug == false) return;

    const auto rect = widget.rect();

    const auto layout = widget.layout();


    // -------------------------------------------------
    // Margin
    // -------------------------------------------------

    DebugPainter::DrawMargin(hdc, rect, layout);

    // -------------------------------------------------
    // Padding
    // -------------------------------------------------

    DebugPainter::DrawPadding(hdc, rect, layout);

    // -------------------------------------------------
    // Widget bounds
    // -------------------------------------------------

    DebugPainter::DrawBounds(hdc, rect);

    // -------------------------------------------------
    // Text
    // -------------------------------------------------

    DebugPainter::DrawTextW(hdc, rect, widget.name());

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

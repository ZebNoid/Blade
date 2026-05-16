#include "LayoutDebugRenderer.h"

#include "Debug/DebugPainter/DebugPainter.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


auto LayoutDebugRenderer::Render(HDC hdc, Widget& widget) -> void
{
    const auto rect = widget.rect();

    const auto layout = widget.layout();

    DebugPainter::DrawTextW(hdc, rect, widget.name());

    // -------------------------------------------------
    // Widget bounds
    // -------------------------------------------------

    DebugPainter::DrawBounds(hdc, rect);

    // -------------------------------------------------
    // Padding
    // -------------------------------------------------

    DebugPainter::DrawPadding(hdc, rect, layout);

    // -------------------------------------------------
    // Margin
    // -------------------------------------------------

    DebugPainter::DrawMargin(hdc, rect, layout);

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

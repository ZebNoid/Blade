#include "StackLayout.h"


namespace Blade {

auto StackLayout::Measure(
    const std::vector<std::unique_ptr<Widget>>& children,
    const LayoutProps& layout,
    Size available
) -> Size
{
    int maxWidth = 0;
    int maxHeight = 0;

    const auto& padding = layout.padding;

    for (const auto& child : children)
    {
        auto size = child->measure(available);

        const auto& margin = child->layout().margin;

        maxWidth = max(
            maxWidth,
            margin.left +
            size.width +
            margin.right
        );

        maxHeight = max(
            maxHeight,
            margin.top +
            size.height +
            margin.bottom
        );
    }

    return {
        maxWidth + padding.left + padding.right,
        maxHeight + padding.top + padding.bottom
    };
}

auto StackLayout::Arrange(
    const std::vector<std::unique_ptr<Widget>>& children,
    const LayoutProps& layout,
    Rect rect
) -> void
{
    const auto& padding = layout.padding;

    Rect contentRect{
        rect.x + padding.left,
        rect.y + padding.top,
        rect.width -
        padding.left -
        padding.right,
        rect.height -
        padding.top -
        padding.bottom
    };

    for (const auto& child : children)
    {
        const auto& margin = child->layout().margin;

        child->arrange({
            contentRect.x + margin.left,
            contentRect.y + margin.top,

            contentRect.width -
            margin.left -
            margin.right,

            contentRect.height -
            margin.top -
            margin.bottom
        });
    }
}


} // namespace

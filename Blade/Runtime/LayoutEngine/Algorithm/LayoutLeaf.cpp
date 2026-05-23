#include "LayoutLeaf.h"

#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutLeaf::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    node.desiredSize = node.layout.size;

    int maxWidth = 0;
    int maxHeight = 0;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{
            .node = &child,
            .available = node.desiredSize
        };

        const auto size =
            LayoutEngine::Measure(
                childCtx
            );

        maxWidth = max(
            maxWidth,
            size.width
        );

        maxHeight = max(
            maxHeight,
            size.height
        );
    }

    if (node.desiredSize.width == 0)
    {
        node.desiredSize.width = maxWidth;
    }

    if (node.desiredSize.height == 0)
    {
        node.desiredSize.height = maxHeight;
    }

    return node.desiredSize;
}

auto LayoutLeaf::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto& padding =
        node.layout.layout.padding;

    const int x =
        ctx.rect.x + padding.left;

    const int y =
        ctx.rect.y + padding.top;

    const int width =
        max(
            0,
            ctx.rect.width -
            padding.left -
            padding.right
        );

    const int height =
        max(
            0,
            ctx.rect.height -
            padding.top -
            padding.bottom
        );

    for (auto& child : node.children)
    {
        const auto size =
            child.desiredSize;

        Api::Rect childRect{
            x,
            y,
            child.layoutType == LayoutType::None
                ? size.width
                : width,
            child.layoutType == LayoutType::None
                ? size.height
                : height
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

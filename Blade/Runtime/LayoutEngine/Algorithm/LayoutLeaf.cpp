#include "LayoutLeaf.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
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

        const auto marginSize =
            LayoutGeometry::Inflate(
                size,
                child.layout.box.margin
            );

        maxWidth = max(
            maxWidth,
            marginSize.width
        );

        maxHeight = max(
            maxHeight,
            marginSize.height
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

    node.desiredSize =
        LayoutGeometry::Inflate(
            node.desiredSize,
            node.layout.box.padding
        );

    return node.desiredSize;
}

auto LayoutLeaf::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    const auto contentRect =
        LayoutGeometry::Deflate(
            ctx.rect,
            node.layout.box.padding
        );

    for (auto& child : node.children)
    {
        const auto size =
            child.desiredSize;

        const auto childContentRect =
            LayoutGeometry::Deflate(
                contentRect,
                child.layout.box.margin
            );

        Api::Rect childRect{
            childContentRect.x,
            childContentRect.y,
            child.layoutType == LayoutType::None
                ? size.width
                : childContentRect.width,
            child.layoutType == LayoutType::None
                ? size.height
                : childContentRect.height
        };

        LayoutContext childCtx{
            .node = &child,
            .rect = childRect
        };

        LayoutEngine::Arrange(childCtx);
    }
}

} // namespace Blade

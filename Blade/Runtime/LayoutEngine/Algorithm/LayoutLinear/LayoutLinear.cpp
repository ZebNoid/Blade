#include "LayoutLinear.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLinearArrange/LayoutLinearArrange.h"
#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"


namespace Blade {

auto LayoutLinear::Measure(LayoutContext& ctx, LayoutAxis axis) -> Api::Size
{
    auto& node = *ctx.node;

    int totalMain = 0;
    int maxCross = 0;
    bool first = true;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = ctx.available };
        const auto size = LayoutEngine::Measure(childCtx);

        if (!first)
        {
            totalMain += node.layout.gap;
        }

        first = false;

        totalMain += LayoutAxisGeometry::MainSize(axis, size);
        maxCross = max(maxCross, LayoutAxisGeometry::CrossSize(axis, size));
    }

    node.desiredSize = LayoutGeometry::Constrain(LayoutGeometry::Inflate(LayoutAxisGeometry::Size(axis, totalMain, maxCross), node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto LayoutLinear::Arrange(LayoutContext& ctx, LayoutAxis axis) -> void
{
    auto& node = *ctx.node;

    const auto contentRect = LayoutGeometry::Deflate(ctx.rect, node.layout.box.padding);
    const auto content = LayoutLinearArrange::MeasureContent(node, contentRect, axis);
    const int itemCount = static_cast<int>(node.children.size());
    const int availableMain = LayoutAxisGeometry::MainRectSize(axis, contentRect);
    const int itemGap = LayoutGeometry::MainAxisGap(node.layout.mainAxisAlignment, node.layout.gap, availableMain, content.size, itemCount);

    int cursor = LayoutAxisGeometry::MainRectPosition(axis, contentRect) +
        LayoutGeometry::MainAxisOffset(node.layout.mainAxisAlignment, availableMain, content.size, itemCount);

    bool first = true;
    LayoutLinearArrange::FlexCursor flexCursor;

    for (auto& child : node.children)
    {
        if (!first)
        {
            cursor += itemGap;
        }

        first = false;

        const int childMain = LayoutLinearArrange::ChildMainSize(child, content, axis, flexCursor);
        const auto cross = LayoutLinearArrange::AlignCrossAxis(node, child, contentRect, axis);

        const auto childRect = LayoutAxisGeometry::Rect(axis, cursor, cross.position, childMain, cross.size);
        LayoutContext childCtx{ .node = &child, .rect = childRect };

        LayoutEngine::Arrange(childCtx);

        cursor += childMain;
    }
}

} // namespace Blade

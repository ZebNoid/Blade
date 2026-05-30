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

        totalMain += Layout::Axis::MainSize(axis, size);
        maxCross = max(maxCross, Layout::Axis::CrossSize(axis, size));
    }

    node.desiredSize = Layout::Geometry::Constrain(Layout::Geometry::Inflate(Layout::Axis::Size(axis, totalMain, maxCross), node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto LayoutLinear::Arrange(LayoutContext& ctx, LayoutAxis axis) -> void
{
    auto& node = *ctx.node;

    const auto contentRect = Layout::Geometry::Deflate(ctx.rect, node.layout.box.padding);
    const auto content = Layout::LinearArrange::MeasureContent(node, contentRect, axis);
    const int itemCount = static_cast<int>(node.children.size());
    const int availableMain = Layout::Axis::MainRectSize(axis, contentRect);
    const int itemGap = Layout::Geometry::MainAxisGap(node.layout.mainAxisAlignment, node.layout.gap, availableMain, content.size, itemCount);

    int cursor = Layout::Axis::MainRectPosition(axis, contentRect) +
        Layout::Geometry::MainAxisOffset(node.layout.mainAxisAlignment, availableMain, content.size, itemCount);

    bool first = true;
    Layout::LinearArrange::FlexCursor flexCursor;

    for (auto& child : node.children)
    {
        if (!first)
        {
            cursor += itemGap;
        }

        first = false;

        const int childMain = Layout::LinearArrange::ChildMainSize(child, content, axis, flexCursor);
        const auto cross = Layout::LinearArrange::AlignCrossAxis(node, child, contentRect, axis);

        const auto childRect = Layout::Axis::Rect(axis, cursor, cross.position, childMain, cross.size);
        LayoutContext childCtx{ .node = &child, .rect = childRect };

        LayoutEngine::Arrange(childCtx);

        cursor += childMain;
    }
}

} // namespace Blade

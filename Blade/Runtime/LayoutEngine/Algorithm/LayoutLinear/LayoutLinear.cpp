#include "LayoutLinear.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLinearArrange/LayoutLinearArrange.h"
#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"

#include <algorithm>


namespace Blade::Layout::Linear {

namespace {

struct MeasuredChildren
{
    int totalMain = 0;
    int maxCross = 0;
};

auto MeasureChildren(LayoutNode& node, Api::Size available, LayoutAxis axis) -> MeasuredChildren
{
    MeasuredChildren result;
    bool first = true;

    for (auto& child : node.children)
    {
        LayoutContext childCtx{ .node = &child, .available = available };
        const auto size = Layout::Engine::Measure(childCtx);

        if (!first)
        {
            result.totalMain += node.layout.gap;
        }

        first = false;

        result.totalMain += Layout::Axis::MainSize(axis, size);
        result.maxCross = (std::max)(result.maxCross, Layout::Axis::CrossSize(axis, size));
    }

    return result;
}

} // namespace

auto Measure(LayoutContext& ctx, LayoutAxis axis) -> Api::Size
{
    auto& node = *ctx.node;
    const auto children = MeasureChildren(node, ctx.available, axis);

    node.desiredSize = Layout::Geometry::Constrain(Layout::Geometry::Inflate(Layout::Axis::Size(axis, children.totalMain, children.maxCross), node.layout.box.padding), node.layout.box.minSize, node.layout.box.maxSize);
    return node.desiredSize;
}

auto Arrange(LayoutContext& ctx, LayoutAxis axis) -> void
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

        Layout::Engine::Arrange(childCtx);

        cursor += childMain;
    }
}

} // namespace Blade::Layout::Linear

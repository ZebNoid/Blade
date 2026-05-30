#include "LayoutLinearArrange.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"


namespace Blade::Layout::LinearArrange {

auto MeasureContent(const LayoutNode& node, const Api::Rect& contentRect, LayoutAxis axis) -> Content
{
    Content content;
    bool first = true;

    for (const auto& child : node.children)
    {
        if (!first)
        {
            content.size += node.layout.gap;
        }

        first = false;

        const int flex = Layout::Geometry::NonNegative(child.layout.box.flex);

        content.size += flex > 0 ? 0 : Layout::Axis::MainSize(axis, child.desiredSize);
        content.totalFlex += flex;
    }

    if (content.totalFlex > 0)
    {
        content.flexSpace = Layout::Geometry::NonNegative(Layout::Axis::MainRectSize(axis, contentRect) - content.size);
        content.size += content.flexSpace;
    }

    return content;
}

auto ChildMainSize(const LayoutNode& child, const Content& content, LayoutAxis axis, FlexCursor& cursor) -> int
{
    const int flex = Layout::Geometry::NonNegative(child.layout.box.flex);

    if (content.totalFlex <= 0 || flex <= 0)
    {
        return Layout::Axis::MainSize(axis, child.desiredSize);
    }

    cursor.usedFlex += flex;

    const int nextUsedSpace = content.flexSpace * cursor.usedFlex / content.totalFlex;
    const int size = nextUsedSpace - cursor.usedSpace;

    cursor.usedSpace = nextUsedSpace;
    return size;
}

auto AlignCrossAxis(const LayoutNode& node, const LayoutNode& child, const Api::Rect& contentRect, LayoutAxis axis) -> CrossAxis
{
    const int available = Layout::Geometry::NonNegative(Layout::Axis::CrossRectSize(axis, contentRect));

    CrossAxis layout{
        .position = Layout::Axis::CrossRectPosition(axis, contentRect),
        .size = Layout::Axis::CrossSize(axis, child.desiredSize)
    };

    switch (node.layout.crossAxisAlignment)
    {
    case CrossAxisAlignment::Center:
        layout.position += Layout::Geometry::NonNegative(available - layout.size) / 2;
        break;

    case CrossAxisAlignment::End:
        layout.position = Layout::Axis::CrossRectPosition(axis, contentRect) +
            Layout::Axis::CrossRectSize(axis, contentRect) -
            layout.size;
        break;

    case CrossAxisAlignment::Stretch:
        layout.size = available;
        break;

    case CrossAxisAlignment::Start:
    default:
        break;
    }

    return layout;
}

} // namespace Blade::Layout::LinearArrange

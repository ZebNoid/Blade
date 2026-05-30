#include "LayoutLinearArrange.h"

#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"


namespace Blade {

auto LayoutLinearArrange::MeasureContent(const LayoutNode& node, const Api::Rect& contentRect, LayoutAxis axis) -> Content
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

        const int flex = LayoutGeometry::NonNegative(child.layout.box.flex);

        content.size += flex > 0 ? 0 : LayoutAxisGeometry::MainSize(axis, child.desiredSize);
        content.totalFlex += flex;
    }

    if (content.totalFlex > 0)
    {
        content.flexSpace = LayoutGeometry::NonNegative(LayoutAxisGeometry::MainRectSize(axis, contentRect) - content.size);
        content.size += content.flexSpace;
    }

    return content;
}

auto LayoutLinearArrange::ChildMainSize(const LayoutNode& child, const Content& content, LayoutAxis axis, FlexCursor& cursor) -> int
{
    const int flex = LayoutGeometry::NonNegative(child.layout.box.flex);

    if (content.totalFlex <= 0 || flex <= 0)
    {
        return LayoutAxisGeometry::MainSize(axis, child.desiredSize);
    }

    cursor.usedFlex += flex;

    const int nextUsedSpace = content.flexSpace * cursor.usedFlex / content.totalFlex;
    const int size = nextUsedSpace - cursor.usedSpace;

    cursor.usedSpace = nextUsedSpace;
    return size;
}

auto LayoutLinearArrange::AlignCrossAxis(const LayoutNode& node, const LayoutNode& child, const Api::Rect& contentRect, LayoutAxis axis) -> CrossAxis
{
    const int available = LayoutGeometry::NonNegative(LayoutAxisGeometry::CrossRectSize(axis, contentRect));

    CrossAxis layout{
        .position = LayoutAxisGeometry::CrossRectPosition(axis, contentRect),
        .size = LayoutAxisGeometry::CrossSize(axis, child.desiredSize)
    };

    switch (node.layout.crossAxisAlignment)
    {
    case CrossAxisAlignment::Center:
        layout.position += LayoutGeometry::NonNegative(available - layout.size) / 2;
        break;

    case CrossAxisAlignment::End:
        layout.position = LayoutAxisGeometry::CrossRectPosition(axis, contentRect) +
            LayoutAxisGeometry::CrossRectSize(axis, contentRect) -
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

} // namespace Blade

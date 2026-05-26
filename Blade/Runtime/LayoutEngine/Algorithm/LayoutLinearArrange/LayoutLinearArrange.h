#pragma once

#include "Common/Rect.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"
#include "Runtime/LayoutEngine/Geometry/LayoutAxis.h"


namespace Blade {

class LayoutLinearArrange
{
public:
    struct Content
    {
        int size = 0;
        int totalFlex = 0;
        int flexSpace = 0;
    };

    struct CrossAxis
    {
        int position = 0;
        int size = 0;
    };

    struct FlexCursor
    {
        int usedFlex = 0;
        int usedSpace = 0;
    };

public:
    static auto MeasureContent(const LayoutNode& node, const Api::Rect& contentRect, LayoutAxis axis) -> Content;
    static auto ChildMainSize(const LayoutNode& child, const Content& content, LayoutAxis axis, FlexCursor& cursor) -> int;
    static auto AlignCrossAxis(const LayoutNode& node, const LayoutNode& child, const Api::Rect& contentRect, LayoutAxis axis) -> CrossAxis;
};

} // namespace Blade

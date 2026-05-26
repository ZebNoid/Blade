#pragma once

#include "Common/Rect.h"
#include "Common/Size.h"
#include "Runtime/LayoutEngine/Data/LayoutNode.h"


namespace Blade {

class LayoutLeafChildren
{
public:
    static auto Measure(LayoutNode& node) -> Api::Size;
    static auto Arrange(LayoutNode& node, const Api::Rect& contentRect) -> void;

private:
    static auto ChildRect(const LayoutNode& child, const Api::Rect& contentRect) -> Api::Rect;
};

} // namespace Blade

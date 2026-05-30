#include "LayoutColumn.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLinear/LayoutLinear.h"


namespace Blade::Layout::Column {

auto Measure(LayoutContext& ctx) -> Api::Size
{
    return Layout::Linear::Measure(ctx, LayoutAxis::Vertical);
}

auto Arrange(LayoutContext& ctx) -> void
{
    Layout::Linear::Arrange(ctx, LayoutAxis::Vertical);
}

} // namespace Blade::Layout::Column

#include "LayoutRow.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLinear/LayoutLinear.h"


namespace Blade::Layout::Row {

auto Measure(LayoutContext& ctx) -> Api::Size
{
    return Layout::Linear::Measure(ctx, LayoutAxis::Horizontal);
}

auto Arrange(LayoutContext& ctx) -> void
{
    Layout::Linear::Arrange(ctx, LayoutAxis::Horizontal);
}

} // namespace Blade::Layout::Row

#include "LayoutRow.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLinear/LayoutLinear.h"


namespace Blade {

auto LayoutRow::Measure(LayoutContext& ctx) -> Api::Size
{
    return LayoutLinear::Measure(ctx, LayoutAxis::Horizontal);
}

auto LayoutRow::Arrange(LayoutContext& ctx) -> void
{
    LayoutLinear::Arrange(ctx, LayoutAxis::Horizontal);
}

} // namespace Blade

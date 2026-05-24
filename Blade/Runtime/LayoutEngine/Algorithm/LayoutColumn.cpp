#include "LayoutColumn.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutLinear.h"


namespace Blade {

auto LayoutColumn::Measure(LayoutContext& ctx) -> Api::Size
{
    return LayoutLinear::Measure(ctx, LayoutAxis::Vertical);
}

auto LayoutColumn::Arrange(LayoutContext& ctx) -> void
{
    LayoutLinear::Arrange(ctx, LayoutAxis::Vertical);
}

} // namespace Blade

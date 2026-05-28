#include "LayoutEngine.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutColumn/LayoutColumn.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutLeaf/LayoutLeaf.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutRow/LayoutRow.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutStack/LayoutStack.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutVirtual/LayoutVirtual.h"


namespace Blade {


auto LayoutEngine::Measure(
    LayoutContext& ctx
) -> Api::Size
{
    auto& node = *ctx.node;

    switch (node.layoutType)
    {
    case LayoutType::Column:
        return LayoutColumn::Measure(ctx);

    case LayoutType::Row:
        return LayoutRow::Measure(ctx);

    case LayoutType::Stack:
        return LayoutStack::Measure(ctx);

    case LayoutType::Virtual:
        return LayoutVirtual::Measure(ctx);

    case LayoutType::None:
    default:
        return LayoutLeaf::Measure(ctx);
    }
}

auto LayoutEngine::Arrange(
    LayoutContext& ctx
) -> void
{
    auto& node = *ctx.node;

    node.rect = ctx.rect;

    switch (node.layoutType)
    {
    case LayoutType::Column:
        LayoutColumn::Arrange(ctx);
        break;

    case LayoutType::Row:
        LayoutRow::Arrange(ctx);
        break;

    case LayoutType::Stack:
        LayoutStack::Arrange(ctx);
        break;

    case LayoutType::Virtual:
        LayoutVirtual::Arrange(ctx);
        break;

    default:
        LayoutLeaf::Arrange(ctx);
        break;
    }
}

} // namespace
